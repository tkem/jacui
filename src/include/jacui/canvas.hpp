/**
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
       \brief JACUI canvas class
    */
    class canvas: public surface {
    public:
        canvas();

        canvas(const canvas& rhs);

        explicit canvas(size2d size);

        canvas(std::size_t width, std::size_t height);

        ~canvas();

        void resize(size2d size);

        void resize(std::size_t width, std::size_t height);

        void swap(canvas& rhs);

        canvas& operator=(const canvas& rhs) {
            canvas tmp(rhs);
            swap(tmp);
            return *this;
        }

    protected:
        detail::surface_type* detail() const;

    private:
        detail::surface_type* detail_;
    };

    inline void swap(canvas& lhs, canvas& rhs) {
        lhs.swap(rhs);
    }
}

#endif