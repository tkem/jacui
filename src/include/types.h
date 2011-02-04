// -*-c++-*-
//
//   $Id$
//

#ifndef JACUI_TYPES_H
#define JACUI_TYPES_H

#include <cstddef>

namespace jacui {
    /**
       \brief JACUI point type
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
       \brief JACUI size type
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
       \brief JACUI rectangle type
    */
    struct rect2d {
        rect2d() : x(0), y(0), width(0), height(0) { }

        rect2d(const size2d& s) : x(0), y(0), width(s.width), height(s.height) { }

        rect2d(std::size_t xsize, std::size_t ysize)
            : x(0), y(0), width(xsize), height(ysize) { }

        rect2d(std::size_t xpos, std::size_t ypos, std::size_t xsize, std::size_t ysize)
            : x(xpos), y(ypos), width(xsize), height(ysize) { }

        bool empty() const { return width == 0 || height == 0; }

        size2d size() const { return size2d(width, height); }

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
       \brief JACUI color type
    */
    struct color {
    public:
        color() : r(0), g(0), b(0), a(0) { }

        explicit color(int gray) : r(gray), g(gray), b(gray), a(0xff) { }

        color(int red, int green, int blue) : r(red), g(green), b(blue), a(0xff) { }

        color(int red, int green, int blue, int alpha) : r(red), g(green), b(blue), a(alpha) { }

        unsigned long rgb() const { return r << 16 | g << 8 | b; }

        unsigned long rgba() const { return r << 24 | g << 16 | b << 8 | a; }

        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };

    /**
       \brief create color from RGB value, e.g. 0xffff00 -> yellow
    */
    inline color make_rgb(unsigned long rgb)
    {
        return color((rgb >> 16) & 0xff, (rgb >> 8) & 0xff, rgb & 0xff);
    }

    /**
       \brief create color from RGBA value, e.g. 0xffff0080 -> yellow with 50% transparency
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
