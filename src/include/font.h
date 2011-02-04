// -*-c++-*-
//
//   $Id$
//

#ifndef JACUI_FONT_H
#define JACUI_FONT_H

#include "canvas.h"

#include <string>

namespace jacui {
    /**
       \brief JACUI font class
    */
    class font {
    public:
        font(const font& rhs);

        font(const font& rhs, float ptsize);

        font(const char* filename, float ptsize);

        font(const void* data, std::size_t size, float ptsize);
        
        ~font();

        float size() const;

        const char* family() const;

        const char* style() const;

        int height() const;

        int ascent() const;

        int descent() const;

        int leading() const;

        size2d size(const std::string& text) const;

        size2d size(const std::wstring& text) const;

        canvas render(const std::string& text, color fg, color bg) const;

        canvas render(const std::wstring& text, color fg, color bg) const;

        void draw(surface& s, const std::string& text, color c, point2d p) const;

        void draw(surface& s, const std::wstring& text, color c, point2d p) const;

        void draw(surface& s, const std::string& text, color c, int x, int y) const;

        void draw(surface& s, const std::wstring& text, color c, int x, int y) const;

        void resize(float ptsize);

        void swap(font& rhs);

        font& operator=(const font& rhs) {
            font tmp(rhs);
            swap(tmp);
            return *this;
        }

    private:
        struct impl;
        impl* pimpl_;
    };

    inline void swap(font& lhs, font& rhs) {
        lhs.swap(rhs);
    }
}

#endif
