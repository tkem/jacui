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

#ifndef JACUI_CURSOR_HPP
#define JACUI_CURSOR_HPP

#include "types.hpp"

namespace jacui {
    namespace detail {
        struct cursor_type;
    }

    /**
       \brief jacui cursor class
    */
    class cursor {
    public:
        /**
           \brief create a cursor from bitmap data

           \param data the bitmap data for the cursor
           \param mask the bitmap mask for the cursor
           \param size the size of the cursor
           \param point the location of the mouse position within the cursor
        */
        cursor(const void* data, const void* mask, const size2d& size, const point2d& point);

        /**
           \brief create a copy an existing cursor

           \param rhs the cursor to be copied
        */
        cursor(const cursor& rhs);

        /**
           \brief destroy a cursor
        */
        ~cursor();

        /**
           \brief swap two cursor instances

           \param rhs the cursor to be swapped
        */
        void swap(cursor& rhs);

        /**
           \brief copy an existing cursor

           \param rhs the cursor to be copied
        */
        cursor& operator=(const cursor& rhs) {
            cursor tmp(rhs);
            swap(tmp);
            return *this;
        }

    public:
        detail::cursor_type* detail() const;

    private:
        struct impl;
        impl* pimpl_;
    };

    /**
       \brief swap two cursor instances

       \param lhs the first cursor to be swapped
       \param rhs the second cursor to be swapped
    */
    inline void swap(cursor& lhs, cursor& rhs) {
        rhs.swap(lhs);
    }
}

#endif
