/*
 * JACUI - Just Another C++ User Interface Library
 *
 * Copyright (C) 2011 The JACUI Project
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

#ifndef JACUI_FONT_HPP
#define JACUI_FONT_HPP

#include "canvas.hpp"

#include <string>

namespace jacui {
    /**
       \brief jacui font class
    */
    class font {
    public:
        /**
           \brief create a copy of an existing font
        */
        font(const font& rhs);

        /**
           \brief create a copy of an existing font with a spezified size
        */
        font(const font& rhs, float ptsize);

        /**
           \brief create a font from a file
        */
        font(const char* filename, float ptsize);

        /**
           \brief create a font from memory
        */
        font(const void* data, std::size_t size, float ptsize);
        
        /**
           \brief destroy a font
        */
        ~font();

        /**
           \brief the point size of this font
        */
        float size() const;

        /**
           \brief the family name of this font
        */
        const char* family() const;

        /**
           \brief the style name of this font
        */
        const char* style() const;

        /**
           \brief the height of this font
        */
        int height() const;

        /**
           \brief the ascent of this font
        */
        int ascent() const;

        /**
           \brief the descent of this font
        */
        int descent() const;

        /**
           \brief the leading of this font
        */
        int leading() const;

        /**
           \brief calculate the size of some text
        */
        size2d size(const std::string& text) const;

        /**
           \brief calculate the size of some text
        */
        size2d size(const std::wstring& text) const;

        /**
           \brief render some text to a canvas
        */
        canvas render(const std::string& text, color fg, color bg) const;

        /**
           \brief render some text to a canvas
        */
        canvas render(const std::wstring& text, color fg, color bg) const;

        /**
           \brief draw some text onto a surface
        */
        void draw(surface& s, const std::string& text, color c, const point2d& p) const;

        /**
           \brief draw some text onto a surface
        */
        void draw(surface& s, const std::wstring& text, color c, const point2d& p) const;

        /**
           \brief draw some text onto a surface
        */
        void draw(surface& s, const std::string& text, color c, int x, int y) const;

        /**
           \brief draw some text onto a surface
        */
        void draw(surface& s, const std::wstring& text, color c, int x, int y) const;

        /**
           \brief resize a font
        */
        void resize(float ptsize);

        /**
           \brief swap two font instances

           \param rhs the font to be swapped
        */
        void swap(font& rhs);

        /**
           \brief copy an existing font

           \param rhs the font to be copied
        */
        font& operator=(const font& rhs) {
            font tmp(rhs);
            swap(tmp);
            return *this;
        }

    private:
        struct impl;
        impl* pimpl_;
    };

    /**
       \brief swap two font instances

       \param lhs the first font to be swapped
       \param rhs the second font to be swapped
    */
    inline void swap(font& lhs, font& rhs) {
        lhs.swap(rhs);
    }
}

#endif
