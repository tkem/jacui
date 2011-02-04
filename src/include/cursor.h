// -*-c++-*-
//
//   $Id$
//

#ifndef JACUI_CURSOR_H
#define JACUI_CURSOR_H

#include "types.h"

namespace jacui {
    /**
       \brief JACUI cursor class
    */
    class cursor {
    public:
        cursor(const cursor& rhs);

        cursor(const void* data, const void* mask, size2d size, point2d point);

        cursor(const char* xpm[], std::size_t x, std::size_t y);

        ~cursor();

        const void* data() const;

        const void* mask() const;

        size2d size() const;

        point2d point() const;

        void swap(cursor& rhs);

        cursor& operator=(const cursor& rhs) {
            cursor tmp(rhs);
            swap(tmp);
            return *this;
        }

    private:
        struct impl;
        impl* pimpl_;
    };

    inline void swap(cursor& lhs, cursor& rhs) {
        rhs.swap(lhs);
    }
}

#endif
