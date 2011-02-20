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

#ifndef JACUI_TYPES_HPP
#define JACUI_TYPES_HPP

#include <cstddef>

/**
   \brief jacui namespace
*/
namespace jacui {
    /**
       \brief jacui point type
    */
    struct point2d {
        point2d() : x(0), y(0) { }

        point2d(std::size_t xpos, std::size_t ypos) : x(xpos), y(ypos) { }

        std::size_t x;
        std::size_t y;
    };

    inline bool operator==(const point2d& lhs, const point2d& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    inline bool operator!=(const point2d& lhs, const point2d& rhs)
    {
        return lhs.x != rhs.x || lhs.y != rhs.y;
    }

    /**
       \brief jacui size type
    */
    struct size2d {
        size2d() : width(0), height(0) { }

        size2d(std::size_t xsize, std::size_t ysize) : width(xsize), height(ysize) { }

        bool empty() const { return width == 0 || height == 0; }

        std::size_t width;
        std::size_t height;
    };

    inline bool operator==(const size2d& lhs, const size2d& rhs)
    {
        return lhs.width == rhs.width && lhs.height == rhs.height;
    }

    inline bool operator!=(const size2d& lhs, const size2d& rhs)
    {
        return lhs.width != rhs.width || lhs.height != rhs.height;
    }

    /**
       \brief jacui rectangle type
    */
    struct rect2d {
        rect2d() : x(0), y(0), width(0), height(0) { }

        rect2d(std::size_t xsize, std::size_t ysize)
            : x(0), y(0), width(xsize), height(ysize) { }

        rect2d(std::size_t xoff, std::size_t yoff, std::size_t xsize, std::size_t ysize)
            : x(xoff), y(yoff), width(xsize), height(ysize) { }

        rect2d(const size2d& s) 
            : x(0), y(0), width(s.width), height(s.height) { }

        rect2d(const point2d& p, const size2d& s) 
            : x(p.x), y(p.y), width(s.width), height(s.height) { }

        bool empty() const { return width == 0 || height == 0; }

        size2d size() const { return size2d(width, height); }

        point2d offset() const { return point2d(x, y); }

        bool includes(const point2d& p) const {
            return includes(p.x, p.y);
        }

        bool includes(std::size_t px, std::size_t py) const {
            return px >= x && py >= y && px < x + width && py < y + height;
        }

        std::size_t x;
        std::size_t y;
        std::size_t width;
        std::size_t height;
    };

    inline bool operator==(const rect2d& lhs, const rect2d& rhs)
    {
        return lhs.x == rhs.x 
            && lhs.y == rhs.y 
            && lhs.width == rhs.width 
            && lhs.height == rhs.height;
    }

    inline bool operator!=(const rect2d& lhs, const rect2d& rhs)
    {
        return lhs.x != rhs.x 
            || lhs.y != rhs.y 
            || lhs.width != rhs.width 
            || lhs.height != rhs.height;
    }

    /**
       \brief jacui color type
    */
    struct color {
    public:
        color() : r(0), g(0), b(0), a(0) { }

        color(int red, int green, int blue) : r(red), g(green), b(blue), a(0xff) { }

        color(int red, int green, int blue, int alpha) : r(red), g(green), b(blue), a(alpha) { }

        bool opaque() const { return a != 0; }

        unsigned long rgb() const { return r << 16 | g << 8 | b; }

        unsigned long rgba() const { return r << 24 | g << 16 | b << 8 | a; }

        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };

    /**
       \brief create color from 24bit RGB value
    */
    inline color make_rgb(unsigned long rgb)
    {
        return color((rgb >> 16) & 0xff, (rgb >> 8) & 0xff, rgb & 0xff);
    }

    /**
       \brief create color from 32bit RGBA value
    */
    inline color make_rgba(unsigned long rgba)
    {
        return color((rgba >> 24) & 0xff, (rgba >> 16) & 0xff, (rgba >> 8) & 0xff, rgba & 0xff);
    }

    inline bool operator==(const color& lhs, const color& rhs)
    {
        return lhs.rgba() == rhs.rgba();
    }

    inline bool operator!=(const color& lhs, const color& rhs)
    {
        return lhs.rgba() != rhs.rgba();
    }
}

#endif
