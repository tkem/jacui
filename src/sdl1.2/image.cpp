// -*-c++-*-
//
//   $Id$
//

#include "jacui/image.h"
#include "detail.h"

#include <algorithm>

#include <SDL/SDL_image.h>

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
    image::image() : detail_(0) 
    { 
    }

    image::image(const image& rhs)
        : detail_(detail::copy_surface(rhs.detail_))
    {
    }

    image::image(const char* filename)
        : detail_(load_image(filename))
    {
    }

    image::image(const void* data, std::size_t size)
        : detail_(load_image(data, size))
    {
    }

    image::~image()
    {
        if (detail_) {
            SDL_FreeSurface(detail_);
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
        std::swap(detail_, rhs.detail_);
    }

    detail::surface_type* image::detail() const
    {
        return detail_;
    }
}
