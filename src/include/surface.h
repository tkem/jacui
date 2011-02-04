// -*-c++-*-
//
//   $Id$
//

#ifndef JACUI_SURFACE_H
#define JACUI_SURFACE_H

#include "types.h"

namespace jacui {
    namespace detail {
        struct surface_type;
    }

    /**
       \brief JACUI surface class
    */
    class surface {
    public:
        virtual ~surface();

        bool empty() const;

        size2d size() const;

        std::size_t width() const;

        std::size_t height() const;

        rect2d clip() const;

        rect2d clip(rect2d r);

        void fill(color c) {
            fill(c, size());
        }

        void fill(color c, rect2d r);

        void blit(const surface& s) {
            blit(s, s.size(), 0, 0);
        }

        void blit(const surface& s, rect2d dst) {
            blit(s, s.size(), dst);
        }

        void blit(const surface& s, point2d dst) {
            blit(s, s.size(), dst);
        }

        void blit(const surface& s, int x, int y) {
            blit(s, s.size(), x, y);
        }

        void blit(const surface& s, rect2d src, rect2d dst);

        void blit(const surface& s, rect2d src, point2d dst);

        void blit(const surface& s, rect2d src, int x, int y);

    protected:
        virtual detail::surface_type* detail() const = 0;
    };
}

#endif
