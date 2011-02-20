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

#ifndef JACUI_SURFACE_HPP
#define JACUI_SURFACE_HPP

#include "types.hpp"

namespace jacui {
    namespace detail {
        struct surface_type;
    }

    /**
       \brief jacui surface class

       A surface represents a collection of pixels onto which the
       application can draw.  Surfaces can exist in purely in memory
       (canvas, image) or in the platform user interface
       (window::view).
    */
    class surface {
    public:
        /**
           \brief destroy a surface
        */
        virtual ~surface();

        /**
           \brief whether the surface is empty
        */
        bool empty() const;

        /**
           \brief the size of this surface
        */
        size2d size() const;

        /**
           \brief the width of this surface
        */
        std::size_t width() const;

        /**
           \brief the height of this surface
        */
        std::size_t height() const;

        /**
           \brief the clipping area of this surface
        */
        rect2d clip() const;

        /**
           \brief set the clipping area of a surface
        */
        rect2d clip(const rect2d& r);

        /**
           \brief fill a surface with a specified color
        */
        void fill(color c) {
            fill(c, size());
        }

        /**
           \brief fill a surface with a specified color
        */
        void fill(color c, const rect2d& r);

        /**
           \brief blit the pixels of another surface to this surface
        */
        void blit(const surface& s) {
            blit(s, s.size(), 0, 0);
        }

        /**
           \brief blit the pixels of another surface to this surface
        */
        void blit(const surface& s, const rect2d& dst) {
            blit(s, s.size(), dst);
        }

        /**
           \brief blit the pixels of another surface to this surface
        */
        void blit(const surface& s, const point2d& dst) {
            blit(s, s.size(), dst);
        }

        /**
           \brief blit the pixels of another surface to this surface
        */
        void blit(const surface& s, int x, int y) {
            blit(s, s.size(), x, y);
        }

        /**
           \brief blit the pixels of another surface to this surface
        */
        void blit(const surface& s, const rect2d& src, const rect2d& dst);

        /**
           \brief blit the pixels of another surface to this surface
        */
        void blit(const surface& s, const rect2d& src, const point2d& dst);

        /**
           \brief blit the pixels of another surface to this surface
        */
        void blit(const surface& s, const rect2d& src, int x, int y);

    public:
        virtual detail::surface_type* detail() const = 0;
    };
}

#endif
