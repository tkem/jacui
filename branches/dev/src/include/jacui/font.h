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
