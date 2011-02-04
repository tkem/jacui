// -*-c++-*-
//
//   $Id$
//

#ifndef JACUI_CURSORS_H
#define JACUI_CURSORS_H

#include "cursor.h"

namespace jacui {
    namespace cursors {
        extern const cursor arrow; // 'auto' and 'default' were not an option

        extern const cursor crosshair;
        extern const cursor pointer;
        extern const cursor move;

        extern const cursor n_resize;
        extern const cursor s_resize;
        extern const cursor e_resize;
        extern const cursor w_resize;

        extern const cursor ne_resize;
        extern const cursor nw_resize;
        extern const cursor se_resize;
        extern const cursor sw_resize;

        extern const cursor text;
        extern const cursor wait;
        extern const cursor progress;
        extern const cursor help;
    }
}

#endif
