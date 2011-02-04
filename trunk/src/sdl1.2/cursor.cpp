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

#include "jacui/cursor.h"
#include "detail.h"

#include <algorithm>
#include <sstream>
#include <string>

namespace jacui {
    struct cursor::impl {
        impl(const void* pd, const void* pm, size2d s, point2d p)
            : data(static_cast<const char*>(pd), s.width / 8 * s.height),
              mask(static_cast<const char*>(pm), s.width / 8 * s.height),
              size(s), point(p)
        {
        }

        impl(const std::string& d, const std::string& m, size2d s, point2d p)
            : data(d), mask(m), size(s), point(p)
        {
        }

        std::string data;
        std::string mask;
        size2d size;
        point2d point;
    };

    cursor::cursor(const void* data, const void* mask, size2d size, point2d point)
        : pimpl_(0)
    {
        if (size.width < 8 || size.height < 8 || size.width % 8 != 0)
            throw error("invalid cursor size");
        if (point.x >= size.width || point.y >= size.height)
            throw error("invalid cursor point");
        pimpl_ = new impl(data, mask, size, point);
    }

    cursor::cursor(const char* xpm[], std::size_t x, std::size_t y) 
        : pimpl_(0)
    {
        std::istringstream is(xpm[0]);
        std::size_t width = 0, height = 0;
        std::size_t num_colors = 0, chars_per_pixel = 0;
        is >> width >> height >> num_colors >> chars_per_pixel;

        if (width < 8 || height < 8 || width % 8 != 0)
            throw error("invalid cursor size");
        if (x >= width || y >= height)
            throw error("invalid cursor point");
        if (num_colors < 2 || num_colors > 3 || chars_per_pixel != 1)
            throw error("invalid cursor xpm format");

        std::size_t pitch = width / 8;
        std::string data(pitch * height, '\0');
        std::string mask(pitch * height, '\0');

        for (std::size_t row = 0; row != height; ++row) {
            for (std::size_t col = 0; col != width; ++col) {
                std::size_t index = row * pitch + col / 8;
                std::size_t value = 1 << 7 - (col % 8);

                switch (xpm[row + 4][col]) {
                case 'X':
                case '+':
                    data[index] |= value;
                    mask[index] |= value;
                    break;

                case '.':
                    mask[index] |= value;
                    break;

                case ' ':
                    break;

                default:
                    throw error("invalid cursor xpm");
                }
            }
        }

        pimpl_ = new impl(data, mask, size2d(width, height), point2d(x, y));
    }

    cursor::~cursor()
    {
        delete pimpl_;
    }

    const void* cursor::data() const
    {
        return pimpl_->data.data();
    }

    const void* cursor::mask() const
    {
        return pimpl_->mask.data();
    }

    size2d cursor::size() const
    {
        return pimpl_->size;
    }

    point2d cursor::point() const
    {
        return pimpl_->point;
    }

    void cursor::swap(cursor& rhs)
    {
        std::swap(pimpl_, rhs.pimpl_);
    }
}