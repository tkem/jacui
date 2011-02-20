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

#ifndef JACUI_IMAGE_HPP
#define JACUI_IMAGE_HPP

#include "surface.hpp"

namespace jacui {
    /**
       \brief jacui image class

       An image represents a surface in memory that has been loaded
       from an external source, i.e. a file or a memory area.
    */
    class image: public surface {
    public:
        /**
           \brief create an empty image
        */
        image();

        /**
           \brief create a copy of an existing image
        */
        image(const image& rhs);

        /**
           \brief create an image from a file
        */
        explicit image(const char* filename);

        /**
           \brief create an image from memory
        */
        image(const void* data, std::size_t size);

        /**
          \brief destroy an image
        */
        ~image();

        /**
          \brief load an image from a file
        */
        void load(const char* filename);

        /**
          \brief load an image from memory
        */
        void load(const void* data, std::size_t size);

        /**
           \brief swap two image instances

           \param rhs the image to be swapped
        */
        void swap(image& rhs);

        /**
           \brief copy an existing image

           \param rhs the image to be swapped
        */
        image& operator=(const image& rhs) {
            image tmp(rhs);
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
       \brief swap two image instances

       \param lhs the first image to be swapped
       \param rhs the second image to be swapped
    */
    inline void swap(image& lhs, image& rhs) {
        lhs.swap(rhs);
    }
}

#endif
