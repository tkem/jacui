// -*-c++-*-
//
//   $Id$
//

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
