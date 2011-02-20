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

#ifndef JACUI_CANVAS_HPP
#define JACUI_CANVAS_HPP

#include "surface.hpp"

namespace jacui {
    /**
       \brief jacui canvas class

       A canvas represents a surface in memory onto which the
       application can draw.
    */
    class canvas: public surface {
    public:
        /**
           \brief create an empty canvas
        */
        canvas();

        /**
           \brief create a copy of an existing canvas

           \param rhs the canvas to be copied
        */
        canvas(const canvas& rhs);

        /**
           \brief create a canvas with a specified size

           \param size the size of the canvas
        */
        explicit canvas(const size2d& size);

        /**
           \brief create a canvas with a specified size

           \param width the width of the canvas
           \param height the height of the canvas
        */
        canvas(std::size_t width, std::size_t height);

        /**
           \brief destroy a canvas
        */
        ~canvas();

        /**
           \brief resize a canvas

           \param size the new size of the canvas
        */
        void resize(const size2d& size);

        /**
           \brief resize a canvas

           \param width the new width of the canvas
           \param height the new height of the canvas
        */
        void resize(std::size_t width, std::size_t height);

        /**
           \brief swap two canvas instances

           \param rhs the canvas to be swapped
        */
        void swap(canvas& rhs);

        /**
           \brief copy an existing canvas

           \param rhs the canvas to be copied
        */
        canvas& operator=(const canvas& rhs) {
            canvas tmp(rhs);
            swap(tmp);
            return *this;
        }

    public:
        /**
           \brief implementation detail
        */
        detail::surface_type* detail() const;

    private:
        struct impl;
        impl* pimpl_;
    };

    /**
       \brief swap two canvas instances

       \param lhs the first canvas to be swapped
       \param rhs the second canvas to be swapped
    */
    inline void swap(canvas& lhs, canvas& rhs) {
        lhs.swap(rhs);
    }
}

#endif
