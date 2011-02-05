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

#include "../jacui/cursor.hpp"
#include "../jacui/error.hpp"
#include "detail.hpp"

namespace {
    jacui::detail::cursor_type* make_cursor(const void* data, const void* mask, jacui::size2d s, jacui::point2d p)
    {
        if (s.width < 8 || s.height < 8 || s.width % 8 != 0)
            throw jacui::error("invalid cursor size");
        if (p.x >= s.width || p.y >= s.height)
            throw jacui::error("invalid cursor point");

        Uint8* udata = static_cast<Uint8*>(const_cast<void*>(data));
        Uint8* umask = static_cast<Uint8*>(const_cast<void*>(mask));
        
        return jacui::detail::make_cursor(
            SDL_CreateCursor(udata, umask, s.width, s.height, p.x, p.y)
            );
    }
}

namespace jacui {
    struct cursor::impl: public detail::cursor_type { 
        static impl* make_impl(detail::cursor_type* p) {
            return static_cast<impl*>(p);
        }
    };

    cursor::cursor(const void* data, const void* mask, size2d size, point2d point)
        : pimpl_(impl::make_impl(make_cursor(data, mask, size, point)))
    {
    }

    cursor::~cursor()
    {
        // cursor are deliberatly never freed
    }

    detail::cursor_type* cursor::detail() const
    {
        return pimpl_;
    }

    void cursor::swap(cursor& rhs)
    {
        std::swap(pimpl_, rhs.pimpl_);
    }
}
