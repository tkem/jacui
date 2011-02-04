// -*-c++-*-
//
//   $Id$
//

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
