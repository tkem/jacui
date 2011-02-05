/**
 * JACUI - Just Another C++ User Interface Library
 *
 * Copyright (C) 2011 The JACUI Project <perlkoenig@gmail.com>
 *
 * http://code.google.com/p/jacui/
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "jacui/window.h"
#include "detail.h"

#include <algorithm>
#include <map>

using namespace jacui::detail;

namespace {
    class wmsurface: public jacui::surface {
    public:
        wmsurface() {
        }

        surface_type* detail() const
        {
            return make_surface(SDL_GetVideoSurface());
        }
    };

    class wmicon: public jacui::xpmicon {
    public:
        wmicon(const xpmicon& icon) : xpmicon(icon) { 
        }

        surface_type* get() const {
            return detail();
        }
    };

    inline SDL_Cursor* make_cursor(const jacui::cursor& c) {
        Uint8* udata = static_cast<Uint8*>(const_cast<void*>(c.data()));
        Uint8* umask = static_cast<Uint8*>(const_cast<void*>(c.mask()));
        
        SDL_Cursor* cursor = SDL_CreateCursor(
            udata, umask, c.size().width, c.size().height, c.point().x, c.point().y
            );
        if (!cursor)
            throw_error("error creating cursor");
        return cursor;
    }

    inline Uint32 make_flags(jacui::window::flags_type f)
    {
        Uint32 flags = SDL_HWSURFACE | SDL_DOUBLEBUF | f;
        flags ^= SDL_RESIZABLE; // inverted!
        return flags;
    }
}

namespace jacui {
    struct window::impl {
        typedef std::map<const void*, SDL_Cursor*> cursor_map;
        typedef cursor_map::iterator cursor_iterator;

        impl(const char* title, std::size_t width, std::size_t height, flags_type f) 
        {
            if (title)
                SDL_WM_SetCaption(title, title);
            if (!SDL_SetVideoMode(width, height, 24, make_flags(f)))
                throw_error("error setting video mode");
        }

        impl(const char* title, const wmicon& icon, std::size_t width, std::size_t height, flags_type f) 
        {
            if (title)
                SDL_WM_SetCaption(title, title);
            if (icon.get())
                SDL_WM_SetIcon(icon.get(), 0);
            if (!SDL_SetVideoMode(width, height, 24, make_flags(f)))
                throw_error("error setting video mode");
        }

        ~impl() {
            std::for_each(cursors.begin(), cursors.end(), free_cursor);
        }

        static void free_cursor(cursor_map::value_type& v) {
            SDL_FreeCursor(v.second);
        }

        detail::event_queue events;
        cursor_map cursors;
        wmsurface surface;
    };

    const window::flags_type window::fullscreen = SDL_FULLSCREEN;

    const window::flags_type window::noresize = SDL_RESIZABLE; // inverted!

    const window::flags_type window::noframe = SDL_NOFRAME;

    window::window(const std::string& title, flags_type f)
        : pimpl_(new impl(title.c_str(), 0, 0, f))
    {
    }

    window::window(const std::string& title, size2d s, flags_type f)
        : pimpl_(new impl(title.c_str(), s.width, s.height, f))
    {
    }

    window::window(const std::string& title, std::size_t width, std::size_t height, flags_type f)
        : pimpl_(new impl(title.c_str(), width, height, f))
    {
    }

    window::window(const std::string& title, const xpmicon& icon, flags_type f)
        : pimpl_(new impl(title.c_str(), icon, 0, 0, f))
    {
    }

    window::window(const std::string& title, const xpmicon& icon, size2d s, flags_type f)
        : pimpl_(new impl(title.c_str(), icon, s.width, s.height, f))
    {
    }

    window::window(const std::string& title, const xpmicon& icon, std::size_t width, std::size_t height, flags_type f)
        : pimpl_(new impl(title.c_str(), icon, width, height, f))
    {
    }

    window::~window()
    {
        delete pimpl_;
    }

    size2d window::size() const
    {
        return pimpl_->surface.size();
    }

    std::size_t window::width() const
    {
        return pimpl_->surface.width();
    }

    std::size_t window::height() const
    {
        return pimpl_->surface.height();
    }

    std::string window::title() const
    {
        char* caption;
        SDL_WM_GetCaption(&caption, 0);
        return std::string(caption ? caption : "");
    }

    std::string window::title(const std::string& s)
    {
        char* caption;
        SDL_WM_GetCaption(&caption, 0);
        SDL_WM_SetCaption(s.c_str(), s.c_str());
        return std::string(caption ? caption : "");
    }

    surface& window::view()
    {
        return pimpl_->surface;
    }

    const surface& window::view() const
    {
        return pimpl_->surface;
    }

    event_queue& window::events()
    {
        return pimpl_->events;
    }

    const event_queue& window::events() const
    {
        return pimpl_->events;
    }

    void window::cursor(const jacui::cursor& c)
    {
        impl::cursor_iterator i = pimpl_->cursors.find(c.data());
        if (i == pimpl_->cursors.end()) {
            i = pimpl_->cursors.insert(
                std::make_pair(c.data(), make_cursor(c))
                ).first;
        }
        SDL_SetCursor(i->second);
    }

    void window::cursor(bool enable)
    {
        SDL_ShowCursor(enable ? SDL_ENABLE : SDL_DISABLE);
    }

    void window::resize(size2d size)
    {
        return resize(size.width, size.height);
    }

    void window::resize(std::size_t width, std::size_t height)
    {
        SDL_Surface* s = SDL_GetVideoSurface();

        if (!s)
            throw_error("error resizing window");
        if (!SDL_SetVideoMode(width, height, 0, s->flags))
            throw_error("error resizing window");
    }

    void window::update()
    {
        SDL_Flip(SDL_GetVideoSurface());
    }

    void window::close()
    {
        pimpl_->events.quit();
    }

}