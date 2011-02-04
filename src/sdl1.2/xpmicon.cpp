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

#include "jacui/xpmicon.h"
#include "detail.h"

#include <SDL/SDL_image.h>

#include <algorithm>

using namespace jacui::detail;

namespace jacui {
    xpmicon::xpmicon(const xpmicon& rhs)
        : detail_(copy_surface(rhs.detail_))
    {
    }

    xpmicon::xpmicon(const char* xpm[])
        : detail_(make_surface(IMG_ReadXPMFromArray(const_cast<char**>(xpm))))
    {
    }

    xpmicon::~xpmicon()
    {
        SDL_FreeSurface(detail_);
    }

    void xpmicon::swap(xpmicon& rhs)
    {
        std::swap(detail_, rhs.detail_);
    }

    detail::surface_type* xpmicon::detail() const
    {
        return detail_;
    }
}
