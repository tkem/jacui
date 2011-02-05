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

#include "jacui/canvas.h"
#include "detail.h"

namespace {
    jacui::detail::surface_type* make_surface(std::size_t width, std::size_t height)
    {
        return jacui::detail::make_surface(
            SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 24, 0, 0, 0, 0)
            );
    }
}

namespace jacui {
    canvas::canvas() : detail_(0) 
    { 
    }

    canvas::canvas(const canvas& rhs) 
        : detail_(detail::copy_surface(rhs.detail_))
    {
    }

    canvas::canvas(size2d size) 
        : detail_(make_surface(size.width, size.height))
    {
    }

    canvas::canvas(std::size_t width, std::size_t height) 
        : detail_(make_surface(width, height))
    {
    }

    canvas::~canvas()
    {
        if (detail_) {
            SDL_FreeSurface(detail_);
        }
    }

    void canvas::resize(size2d size)
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
        std::swap(detail_, rhs.detail_);
    }

    detail::surface_type* canvas::detail() const
    {
        return detail_;
    }
}
