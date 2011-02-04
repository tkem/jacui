// -*-c++-*-
//
//   $Id$
//

#ifndef JACUI_CANVAS_H
#define JACUI_CANVAS_H

#include "surface.h"

namespace jacui {
    /**
       \brief JACUI canvas class
    */
    class canvas: public surface {
    public:
        canvas();

        canvas(const canvas& rhs);

        explicit canvas(size2d size);

        canvas(std::size_t width, std::size_t height);

        ~canvas();

        void resize(size2d size);

        void resize(std::size_t width, std::size_t height);

        void swap(canvas& rhs);

        canvas& operator=(const canvas& rhs) {
            canvas tmp(rhs);
            swap(tmp);
            return *this;
        }

    protected:
        detail::surface_type* detail() const;

    private:
        detail::surface_type* detail_;
    };

    inline void swap(canvas& lhs, canvas& rhs) {
        lhs.swap(rhs);
    }
}

#endif
