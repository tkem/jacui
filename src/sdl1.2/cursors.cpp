/*
 * JACUI - Just Another C++ User Interface Library
 *
 * Copyright (C) 2011 The JACUI Project
 *
 * http://code.google.com/p/jacui/
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "jacui/cursors.hpp"
#include "jacui/error.hpp"

#include <sstream>

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

namespace {
    jacui::cursor make_xpm_cursor(const char* xpm[], std::size_t x, std::size_t y) 
    {
        using namespace jacui;

        std::istringstream is(xpm[0]);
        std::size_t width = 0, height = 0;
        std::size_t num_colors = 0, chars_per_pixel = 0;
        is >> width >> height >> num_colors >> chars_per_pixel;

        if (width < 8 || height < 8 || width % 8 != 0)
            throw error("invalid cursor size");
        if (x >= width || y >= height)
            throw error("invalid cursor point");
        if (num_colors < 2 || num_colors > 3 || chars_per_pixel != 1)
            throw error("invalid cursor xpm format");

        std::size_t pitch = width / 8;
        std::string data(pitch * height, '\0');
        std::string mask(pitch * height, '\0');

        for (std::size_t row = 0; row != height; ++row) {
            for (std::size_t col = 0; col != width; ++col) {
                std::size_t index = row * pitch + col / 8;
                std::size_t value = 1 << (7 - col % 8);

                switch (xpm[row + 4][col]) {
                case 'X':
                case '+':
                    data[index] |= value;
                    mask[index] |= value;
                    break;

                case '.':
                    mask[index] |= value;
                    break;

                case ' ':
                    break;

                default:
                    throw error("invalid cursor xpm");
                }
            }
        }

        return cursor(data.data(), mask.data(), size2d(width, height), point2d(x, y));
    }
}

namespace jacui {
    namespace cursors {
        const cursor& arrow()
        {
            static cursor c = make_xpm_cursor(arrow_xpm, 0, 0);
            return c;
        }

        const cursor& crosshair()
        {
            static cursor c = make_xpm_cursor(crosshair_xpm, 7, 7);
            return c;
        }

        const cursor& n_resize()
        {
            static cursor c = make_xpm_cursor(n_resize_xpm, 7, 0);
            return c;
        }

        const cursor& s_resize()
        {
            static cursor c = make_xpm_cursor(s_resize_xpm, 7, 15);
            return c;
        }

        const cursor& e_resize()
        {
            static cursor c = make_xpm_cursor(e_resize_xpm, 15, 7);
            return c;
        }

        const cursor& w_resize()
        { 
            static cursor c = make_xpm_cursor(w_resize_xpm, 0, 7);
            return c;
        }

        const cursor& ne_resize()
        {
            static cursor c = make_xpm_cursor(ne_resize_xpm, 15, 0);
            return c;
        }

        const cursor& nw_resize()
        {
            static cursor c = make_xpm_cursor(nw_resize_xpm, 0, 0);
            return c;
        }

        const cursor& se_resize()
        {
            static cursor c = make_xpm_cursor(se_resize_xpm, 15, 15);
            return c;
        }

        const cursor& sw_resize()
        {
            static cursor c = make_xpm_cursor(sw_resize_xpm, 0, 15);
            return c;
        }

        // additional W3C CSS cursor values:
        // - move
        // - pointer
        // - text
        // - wait
        // - progress
        // - help
    }
}
