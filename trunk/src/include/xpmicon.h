// -*-c++-*-
//
//   $Id$
//

#ifndef JACUI_XPMICON_H
#define JACUI_XPMICON_H

#include "surface.h"

namespace jacui {
    /**
       \brief JACUI xpm icon class
    */
    class xpmicon: public surface {
    public:
        xpmicon(const xpmicon& rhs);

        explicit xpmicon(const char* xpm[]);

        ~xpmicon();

        void swap(xpmicon& rhs);

        xpmicon& operator=(const xpmicon& rhs) {
            xpmicon tmp(rhs);
            swap(tmp);
            return *this;
        }

    protected:
        detail::surface_type* detail() const;

    private:
        detail::surface_type* detail_;
    };

    inline void swap(xpmicon& lhs, xpmicon& rhs) {
        lhs.swap(rhs);
    }
}

#endif
