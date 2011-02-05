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

#include "jacui/image.hpp"
#include "detail.hpp"

#include <algorithm>

#include <SDL_image.h>

namespace {
    jacui::detail::surface_type* load_image(const char* filename)
    {
        return jacui::detail::make_surface(IMG_Load(filename));
    }

    jacui::detail::surface_type* load_image(const void* data, std::size_t size)
    {
        return jacui::detail::make_surface(
            IMG_Load_RW(jacui::detail::make_rwops(data, size), 1)
            );
    }
}

namespace jacui {
    struct image::impl: public detail::surface_type { 
        static impl* make_impl(detail::surface_type* p) {
            return static_cast<impl*>(p);
        }
    };

    image::image() : pimpl_(0) 
    { 
    }

    image::image(const image& rhs)
        : pimpl_(impl::make_impl(detail::copy_surface(rhs.pimpl_)))
    {
    }

    image::image(const char* filename)
        : pimpl_(impl::make_impl(load_image(filename)))
    {
    }

    image::image(const void* data, std::size_t size)
        : pimpl_(impl::make_impl(load_image(data, size)))
    {
    }

    image::~image()
    {
        if (pimpl_) {
            SDL_FreeSurface(pimpl_);
        }
    }

    void image::load(const char* filename)
    {
        image tmp(filename);
        swap(tmp);
    }

    void image::load(const void* data, std::size_t size)
    {
        image tmp(data, size);
        swap(tmp);
    }

    void image::swap(image& rhs)
    {
        std::swap(pimpl_, rhs.pimpl_);
    }

    detail::surface_type* image::detail() const
    {
        return pimpl_;
    }
}
