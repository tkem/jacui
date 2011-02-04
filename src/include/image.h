// -*-c++-*-
//
//   $Id$
//

#ifndef JACUI_IMAGE_H
#define JACUI_IMAGE_H

#include "surface.h"

namespace jacui {
    /**
       \brief JACUI image class
    */
    class image: public surface {
    public:
        image();

        image(const image& rhs);

        explicit image(const char* filename);

        image(const void* data, std::size_t size);

        ~image();

        void load(const char* filename);

        void load(const void* data, std::size_t size);

        void swap(image& rhs);

        image& operator=(const image& rhs) {
            image tmp(rhs);
            swap(tmp);
            return *this;
        }

    protected:
        detail::surface_type* detail() const;

    private:
        detail::surface_type* detail_;
    };

    inline void swap(image& lhs, image& rhs) {
        lhs.swap(rhs);
    }
}

#endif
