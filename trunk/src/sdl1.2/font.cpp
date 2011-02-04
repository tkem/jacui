// -*-c++-*-
//
//   $Id$
//

#include "font.h"
#include "detail.h"

#include <SDL/SDL_ttf.h>

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>

using namespace jacui::detail;

namespace {
    class rendered: public jacui::surface {
    public:
        rendered(TTF_Font* f, const char* s, SDL_Color fg) 
            : detail_(make_surface(TTF_RenderUTF8_Blended(f, s, fg)))
        {
        }

        rendered(TTF_Font* f, const char* s, SDL_Color fg, SDL_Color bg) 
            : detail_(make_surface(TTF_RenderUTF8_Shaded(f, s, fg, bg)))
        {
        }

        rendered(TTF_Font* f, const Uint16* s, SDL_Color fg) 
            : detail_(make_surface(TTF_RenderUNICODE_Blended(f, s, fg)))
        {
        }

        rendered(TTF_Font* f, const Uint16* s, SDL_Color fg, SDL_Color bg) 
            : detail_(make_surface(TTF_RenderUNICODE_Shaded(f, s, fg, bg)))
        {
        }

        ~rendered() 
        {
            SDL_FreeSurface(detail_);
        }

    private:
        surface_type* detail() const { return detail_; }

    private:
        surface_type* detail_;
    };
}

namespace jacui {
    struct font::impl { 
        // rely on std::string's efficient memory handling
        typedef std::string buffer_type;
        
        impl(const buffer_type& buf, float ptsize)
            : buffer(buf), font(0), size(0)
        {
            resize(ptsize);
        }

        impl(const void* data, std::size_t size, float ptsize)
            : buffer(static_cast<const char*>(data), size), font(0), size(0)
        {
            resize(ptsize);
        }

        impl(const char* filename, float ptsize)
            : font(0), size(0)
        {
            std::ifstream is(filename);
            std::istreambuf_iterator<char> i(is);
            std::istreambuf_iterator<char> end;
            buffer.reserve(65536); // actually a quite small ttf
            std::copy(i, end, std::back_inserter(buffer));
            resize(ptsize);
        }

        ~impl() {
            if (font) {
                TTF_CloseFont(font);
            }
        }
    
        void resize(float ptsize) {
            TTF_Font* f = TTF_OpenFontRW(make_rwops(buffer), 1, ptsize);
            if (!f)
                throw_error("error creating font");
            if (font)
                TTF_CloseFont(font);
            font = f;
            size = ptsize;
        }

        buffer_type buffer;
        TTF_Font* font;
        int size;
    };

    font::font(const font& rhs)
        : pimpl_(new impl(rhs.pimpl_->buffer, rhs.pimpl_->size))
    {
    }

    font::font(const font& rhs, float ptsize)
        : pimpl_(new impl(rhs.pimpl_->buffer, ptsize))
    {
    }

    font::font(const char* filename, float ptsize) 
        : pimpl_(new impl(filename, ptsize))
    {
    }

    font::font(const void* data, std::size_t size, float ptsize)
        : pimpl_(new impl(data, size, ptsize))
    {
    }

    font::~font()
    {
        delete pimpl_;
    }

    float font::size() const
    {
        return pimpl_->size;
    }

    const char* font::family() const
    {
        return TTF_FontFaceFamilyName(pimpl_->font);
    }

    const char* font::style() const
    {
        return TTF_FontFaceStyleName(pimpl_->font);
    }

    int font::height() const
    {
        return std::max(TTF_FontLineSkip(pimpl_->font), TTF_FontHeight(pimpl_->font));
    }

    int font::ascent() const
    {
        return TTF_FontAscent(pimpl_->font);
    }

    int font::descent() const
    {
        return TTF_FontHeight(pimpl_->font) - TTF_FontAscent(pimpl_->font);
    }

    int font::leading() const
    {
        return std::max(TTF_FontLineSkip(pimpl_->font) - TTF_FontHeight(pimpl_->font), 0);
    }

    size2d font::size(const std::string& text) const
    {
        int width = 0, height = 0;
        if (!text.empty()) {
            if (TTF_SizeUTF8(pimpl_->font, text.c_str(), &width, &height) < 0) {
                throw_error("error getting text size");
            }
        }
        return size2d(width, height);
    }

    size2d font::size(const std::wstring& text) const
    {
        int width = 0, height = 0;
        if (!text.empty()) {
            // assume wchar_t is (widened) UTF-16
            std::vector<Uint16> uc(text.begin(), text.end());
            uc.push_back(0);

            if (TTF_SizeUNICODE(pimpl_->font, &uc[0], &width, &height) < 0) {
                throw_error("error getting text size");
            }
        }
        return size2d(width, height);
    }

    canvas font::render(const std::string& text, color fg, color bg) const
    {
        canvas res;
        if (!text.empty()) {
            rendered tmp(pimpl_->font, text.c_str(), make_color(fg), make_color(bg));
            res.resize(tmp.size());
            res.blit(tmp);
        }
        return res;
    }

    canvas font::render(const std::wstring& text, color fg, color bg) const
    {
        canvas res;
        if (!text.empty()) {
            // assume wchar_t is (widened) UTF-16
            std::vector<Uint16> uc(text.begin(), text.end());
            uc.push_back(0);

            rendered tmp(pimpl_->font, &uc[0], make_color(fg), make_color(bg));
            res.resize(tmp.size());
            res.blit(tmp);
        }
        return res;
    }

    void font::draw(surface& s, const std::string& text, color c, point2d p) const
    {
        draw(s, text, c, p.x, p.y);
    }

    void font::draw(surface& s, const std::wstring& text, color c, point2d p) const
    {
        draw(s, text, c, p.x, p.y);
    }

    void font::draw(surface& s, const std::string& text, color c, int x, int y) const
    {
        if (!text.empty()) {
            rendered tmp(pimpl_->font, text.c_str(), make_color(c));
            s.blit(tmp, x, y - TTF_FontAscent(pimpl_->font));
        }
    }

    void font::draw(surface& s, const std::wstring& text, color c, int x, int y) const
    {
        if (!text.empty()) {
            // assume wchar_t is (widened) UTF-16
            std::vector<Uint16> uc(text.begin(), text.end());
            uc.push_back(0);

            rendered tmp(pimpl_->font, &uc[0], make_color(c));
            s.blit(tmp, x, y - TTF_FontAscent(pimpl_->font));
        }
    }

    void font::resize(float ptsize)
    {
        pimpl_->resize(ptsize);
    }

    void font::swap(font& rhs)
    {
        std::swap(pimpl_, rhs.pimpl_);
    }
}
