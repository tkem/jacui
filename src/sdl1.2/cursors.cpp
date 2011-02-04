// -*-c++-*-
//
//   $Id$
//

#include "cursors.h"

namespace {
    const char* arrow_xpm[] = {
        "   16   16   3  1",
        "X c #000000",
        ". c #ffffff",
        "  c None",
        "..              ",
        ".X.             ",
        ".XX.            ",
        ".XXX.           ",
        ".XXXX.          ",
        ".XXXXX.         ",
        ".XXXXXX.        ",
        ".XXXXXXX.       ",
        ".XXXXXXXX.      ",
        ".XXXXX.....     ",
        ".XX.XX.         ",
        ".X. .XX.        ",
        "..  .XX.        ",
        ".    .XX.       ",
        "     .XX.       ",
        "      ..        "
    };

    const char* crosshair_xpm[] = {
        "   16   16   3  1",
        "X c #000000",
        ". c #ffffff",
        "  c None",
        "                ",
        "      .X.       ",
        "      .X.       ",
        "      .X.       ",
        "      .X.       ",
        "      .X.       ",
        " ......X......  ",
        " XXXXXXXXXXXXX  ",
        " ......X......  ",
        "      .X.       ",
        "      .X.       ",
        "      .X.       ",
        "      .X.       ",
        "      .X.       ",
        "                ",
        "                "
    };

    const char* n_resize_xpm[] = {
        "   16   16   3  1",
        "X c #000000",
        ". c #ffffff",
        "  c None",
        " .............. ",
        " .XXXXXXXXXXXX. ",
        " .XXXXXXXXXXXX. ",
        " .............. ",
        "      .XX.      ",
        "     .XXXX.     ",
        "    .XXXXXX.    ",
        "   .XX.XX.XX.   ",
        "  .XX..XX..XX.  ",
        "  .X. .XX. .X.  ",
        "   .  .XX.  .   ",
        "      .XX.      ",
        "      .XX.      ",
        "      .XX.      ",
        "      .XX.      ",
        "      ....      "
    };

    const char* s_resize_xpm[] = {
        "   16   16   3  1",
        "X c #000000",
        ". c #ffffff",
        "  c None",
        "      ....      ",
        "      .XX.      ",
        "      .XX.      ",
        "      .XX.      ",
        "      .XX.      ",
        "   .  .XX.  .   ",
        "  .X. .XX. .X.  ",
        "  .XX..XX..XX.  ",
        "   .XX.XX.XX.   ",
        "    .XXXXXX.    ",
        "     .XXXX.     ",
        "      .XX.      ",
        " .............. ",
        " .XXXXXXXXXXXX. ",
        " .XXXXXXXXXXXX. ",
        " .............. "
    };

    const char* e_resize_xpm[] = {
        "   16   16   3  1",
        "X c #000000",
        ". c #ffffff",
        "  c None",
        "                ",
        "            ....",
        "      ..    .XX.",
        "     .XX.   .XX.",
        "      .XX.  .XX.",
        "       .XX. .XX.",
        ".........XX..XX.",
        ".XXXXXXXXXXX.XX.",
        ".XXXXXXXXXXX.XX.",
        ".........XX..XX.",
        "       .XX. .XX.",
        "      .XX.  .XX.",
        "     .XX.   .XX.",
        "      ..    .XX.",
        "            ....",
        "                "
    };

    const char* w_resize_xpm[] = {
        "   16   16   3  1",
        "X c #000000",
        ". c #ffffff",
        "  c None",
        "                ",
        "....            ",
        ".XX.    ..      ",
        ".XX.   .XX.     ",
        ".XX.  .XX.      ",
        ".XX. .XX.       ",
        ".XX..XX.........",
        ".XX.XXXXXXXXXXX.",
        ".XX.XXXXXXXXXXX.",
        ".XX..XX.........",
        ".XX. .XX.       ",
        ".XX.  .XX.      ",
        ".XX.   .XX.     ",
        ".XX.    ..      ",
        "....            ",
        "                "
    };

    const char* nw_resize_xpm[] = {
        "   16   16   3  1",
        "X c #000000",
        ". c #ffffff",
        "  c None",
        "..............  ",
        ".XXXXXXXXXXXX.  ",
        ".XXXXXXXXXXXX.  ",
        ".XX...........  ",
        ".XX.XXXXXXXX.   ",
        ".XX.XXX......   ",
        ".XX.XXXX.       ",
        ".XX.X.XXX.      ",
        ".XX.X..XXX.     ",
        ".XX.X. .XXX.    ",
        ".XX.X.  .XXX.   ",
        ".XX.X.   .XX.   ",
        ".XX...    ...   ",
        "....            ",
        "                ",
        "                "
    };

    const char* ne_resize_xpm[] = {
        "   16   16   3  1",
        "X c #000000",
        ". c #ffffff",
        "  c None",
        "  ..............",
        "  .XXXXXXXXXXXX.",
        "  .XXXXXXXXXXXX.",
        "  ...........XX.",
        "   .XXXXXXXX.XX.",
        "   ......XXX.XX.",
        "       .XXXX.XX.",
        "      .XXX.X.XX.",
        "     .XXX..X.XX.",
        "    .XXX. .X.XX.",
        "   .XXX.  .X.XX.",
        "   .XX.   .X.XX.",
        "   ...    ...XX.",
        "            ....",
        "                ",
        "                "
    };

    const char* se_resize_xpm[] = {
        "   16   16   3  1",
        "X c #000000",
        ". c #ffffff",
        "  c None",
        "                ",
        "                ",
        "            ....",
        "   ...    ...XX.",
        "   .XX.   .X.XX.",
        "   .XXX.  .X.XX.",
        "    .XXX. .X.XX.",
        "     .XXX..X.XX.",
        "      .XXX.X.XX.",
        "       .XXXX.XX.",
        "   ......XXX.XX.",
        "   .XXXXXXXX.XX.",
        "  ...........XX.",
        "  .XXXXXXXXXXXX.",
        "  .XXXXXXXXXXXX.",
        "  .............."
    };

    const char* sw_resize_xpm[] = {
        "   16   16   3  1",
        "X c #000000",
        ". c #ffffff",
        "  c None",
        "                ",
        "                ",
        "....            ",
        ".XX...    ...   ",
        ".XX.X.   .XX.   ",
        ".XX.X.  .XXX.   ",
        ".XX.X. .XXX.    ",
        ".XX.X..XXX.     ",
        ".XX.X.XXX.      ",
        ".XX.XXXX.       ",
        ".XX.XXX......   ",
        ".XX.XXXXXXXX.   ",
        ".XX...........  ",
        ".XXXXXXXXXXXX.  ",
        ".XXXXXXXXXXXX.  ",
        "..............  "
    };

}

namespace jacui {
    namespace cursors {
        const cursor arrow(arrow_xpm, 0, 0);
        const cursor crosshair(crosshair_xpm, 7, 7);

        // const cursor pointer(pointer_xpm, 0, 0);
        // const cursor move(move_xpm, 0, 0);

        const cursor n_resize(n_resize_xpm, 7, 0);
        const cursor s_resize(s_resize_xpm, 7, 15);
        const cursor e_resize(e_resize_xpm, 15, 7);
        const cursor w_resize(w_resize_xpm, 0, 7);

        const cursor ne_resize(ne_resize_xpm, 15, 0);
        const cursor nw_resize(nw_resize_xpm, 0, 0);
        const cursor se_resize(se_resize_xpm, 15, 15);
        const cursor sw_resize(sw_resize_xpm, 0, 15);

        // const cursor text(crosshair_xpm, 0, 0);
        // const cursor wait(crosshair_xpm, 0, 0);
        // const cursor progress(crosshair_xpm, 0, 0);
        // const cursor help(crosshair_xpm, 0, 0);
    }
}
