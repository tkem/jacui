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
        /**
           \brief create a point with zero coordinates
        */
        point2d() : x(0), y(0) { }

        /**
           \brief create a point with specified coordinates
        */
        point2d(std::size_t xpos, std::size_t ypos) : x(xpos), y(ypos) { }

        /**
           \brief the point's x coordinate
        */
        std::size_t x;

        /**
           \brief the point's y coordinate
        */
        std::size_t y;
    };

    /**
       \brief compare two points
    */
    inline bool operator==(const point2d& lhs, const point2d& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    /**
       \brief compare two points
    */
    inline bool operator!=(const point2d& lhs, const point2d& rhs)
    {
        return lhs.x != rhs.x || lhs.y != rhs.y;
    }

    /**
       \brief jacui size type
    */
    struct size2d {
        /**
           \brief create an empty size
        */
        size2d() : width(0), height(0) { }

        /**
           \brief create a size with specified width and height
        */
        size2d(std::size_t xsize, std::size_t ysize) : width(xsize), height(ysize) { }

        /**
           \brief whether the size is empty
        */
        bool empty() const { return width == 0 || height == 0; }

        /**
           \brief the size's width
        */
        std::size_t width;

        /**
           \brief the size's height
        */
        std::size_t height;
    };

    /**
       \brief compare two sizes
    */
    inline bool operator==(const size2d& lhs, const size2d& rhs)
    {
        return lhs.width == rhs.width && lhs.height == rhs.height;
    }

    /**
       \brief compare two sizes
    */
    inline bool operator!=(const size2d& lhs, const size2d& rhs)
    {
        return lhs.width != rhs.width || lhs.height != rhs.height;
    }

    /**
       \brief jacui rectangle type
    */
    struct rect2d {
        /**
           \brief create an empty rectangle
        */
        rect2d() : x(0), y(0), width(0), height(0) { }

        /**
           \brief create a rectangle with spezified size
        */
        rect2d(const size2d& s) 
            : x(0), y(0), width(s.width), height(s.height) { }

        /**
           \brief create a rectangle with spezified size
        */
        rect2d(std::size_t xsize, std::size_t ysize)
            : x(0), y(0), width(xsize), height(ysize) { }

        /**
           \brief create a rectangle with spezified size and offset
        */
        rect2d(std::size_t xoff, std::size_t yoff, std::size_t xsize, std::size_t ysize)
            : x(xoff), y(yoff), width(xsize), height(ysize) { }

        /**
           \brief create a rectangle with spezified size and offset
        */
        rect2d(const point2d& p, const size2d& s) 
            : x(p.x), y(p.y), width(s.width), height(s.height) { }

        /**
           \brief whether the rectangle is empty
        */
        bool empty() const { return width == 0 || height == 0; }

        /**
           \brief the rectangle's size
        */
        size2d size() const { return size2d(width, height); }

        /**
           \brief the rectangle's offset
        */
        point2d offset() const { return point2d(x, y); }

        /**
           \brief whether the rectangle includes a give point
        */
        bool includes(const point2d& p) const {
            return includes(p.x, p.y);
        }

        /**
           \brief whether the rectangle includes a give point
        */
        bool includes(std::size_t px, std::size_t py) const {
            return px >= x && py >= y && px < x + width && py < y + height;
        }

        /**
           \brief the rectangle's x offset
        */
        std::size_t x;

        /**
           \brief the rectangle's y offset
        */
        std::size_t y;

        /**
           \brief the rectangle's width
        */
        std::size_t width;

        /**
           \brief the rectangle's height
        */
        std::size_t height;
    };

    /**
       \brief compare two rectangles
    */
    inline bool operator==(const rect2d& lhs, const rect2d& rhs)
    {
        return lhs.x == rhs.x 
            && lhs.y == rhs.y 
            && lhs.width == rhs.width 
            && lhs.height == rhs.height;
    }

    /**
       \brief compare two rectangles
    */
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
        /**
           \brief create a fully transparent color
        */
        color() : r(0), g(0), b(0), a(0) { }

        /**
           \brief create a color from specified RGB components
        */
        color(int red, int green, int blue) : r(red), g(green), b(blue), a(0xff) { }

        /**
           \brief create a color from specified RGBA components
        */
        color(int red, int green, int blue, int alpha) : r(red), g(green), b(blue), a(alpha) { }

        /**
           \brief whether the color is opaque
        */
        bool opaque() const { return a != 0; }

        /**
           \brief the color's 24 bit RGB value
        */
        unsigned long rgb() const { return r << 16 | g << 8 | b; }

        /**
           \brief the color's 32 bit RGBA value
        */
        unsigned long rgba() const { return r << 24 | g << 16 | b << 8 | a; }

        /**
           \brief the color's red component
        */
        unsigned char r;

        /**
           \brief the color's green component
        */
        unsigned char g;

        /**
           \brief the color's blue component
        */
        unsigned char b;

        /**
           \brief the color's alpha component
        */
        unsigned char a;
    };

    /**
       \brief create a color from a 24 bit RGB value
    */
    inline color make_rgb(unsigned long rgb)
    {
        return color((rgb >> 16) & 0xff, (rgb >> 8) & 0xff, rgb & 0xff);
    }

    /**
       \brief create a color from a 32 bit RGBA value
    */
    inline color make_rgba(unsigned long rgba)
    {
        return color((rgba >> 24) & 0xff, (rgba >> 16) & 0xff, (rgba >> 8) & 0xff, rgba & 0xff);
    }

    /**
       \brief compare two colors
    */
    inline bool operator==(const color& lhs, const color& rhs)
    {
        return lhs.rgba() == rhs.rgba();
    }

    /**
       \brief compare two colors
    */
    inline bool operator!=(const color& lhs, const color& rhs)
    {
        return lhs.rgba() != rhs.rgba();
    }
}

#endif
