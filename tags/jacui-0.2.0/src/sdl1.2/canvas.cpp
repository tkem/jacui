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

#include "jacui/canvas.hpp"
#include "detail.hpp"

namespace {
    jacui::detail::surface_type* make_surface(std::size_t width, std::size_t height)
    {
        return jacui::detail::make_surface(
            SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 24, 0, 0, 0, 0)
            );
    }
}

namespace jacui {
    struct canvas::impl: public detail::surface_type { 
        static impl* make_impl(detail::surface_type* p) {
            return static_cast<impl*>(p);
        }
    };

    canvas::canvas() : pimpl_(0) 
    { 
    }

    canvas::canvas(const canvas& rhs) 
        : pimpl_(impl::make_impl(detail::copy_surface(rhs.pimpl_)))
    {
    }

    canvas::canvas(const size2d& size) 
        : pimpl_(impl::make_impl(make_surface(size.width, size.height)))
    {
    }

    canvas::canvas(std::size_t width, std::size_t height) 
        : pimpl_(impl::make_impl(make_surface(width, height)))
    {
    }

    canvas::~canvas()
    {
        if (pimpl_) {
            SDL_FreeSurface(pimpl_);
        }
    }

    void canvas::resize(const size2d& size)
    {
        canvas tmp(size);
        tmp.blit(*this);
        swap(tmp);
    }

    void canvas::resize(std::size_t width, std::size_t height)
    {
        canvas tmp(width, height);
        tmp.blit(*this);
        swap(tmp);
    }

    void canvas::swap(canvas& rhs)
    {
        std::swap(pimpl_, rhs.pimpl_);
    }

    detail::surface_type* canvas::detail() const
    {
        return pimpl_;
    }
}
