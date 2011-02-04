// -*-c++-*-
//
//   $Id$
//

#ifndef JACUI_ERROR_H
#define JACUI_ERROR_H

#include <stdexcept>

namespace jacui {
    /**
       \brief Generic JACUI exception class
    */
    class error: public std::runtime_error {
    public:
        explicit error(const std::string& msg) 
            : runtime_error(msg) { }
    };
}

#endif
