/**
 * JACUI - Just Another C++ User Interface Library
 *
 * Copyright (C) 2011 The JACUI Project <perlkoenig@gmail.com>
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

#include "bitstream_vera.h"

#include "jacui/window.h"
#include "jacui/event.h"
#include "jacui/font.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include <getopt.h>

using namespace jacui;

void usage(std::ostream& os, const char* name) 
{
    os << "Usage: " << name << " [ OPTION ] [ TEXT ]\n"
       << "Options:\n"
       << "  -f FONTFILE      TrueType font file\n"
       << "  -s FONTSIZE      font size in points\n"
       << "  -u               read unicode from stdin\n"
       << std::endl;
}

int main(int argc, char* argv[])
{
    std::setlocale(LC_CTYPE, "");
    
    font f(bitstream_vera_ttf, sizeof bitstream_vera_ttf, 12);
    bool unicode = false;
    float ptsize = 12;

    // testing and debugging
    bool use_canvas = false;
    int dy = 0;

    // parse command line options
    for (int c; (c = ::getopt(argc, argv, "cf:s:uy:")) > 0; ) {
        switch(c) {
        case 'c':
            use_canvas = true;
            break;

        case 'f':
            f = font(::optarg, ptsize);
            break;

        case 's':
            ptsize = std::strtof(::optarg, 0);
            break;

        case 'u':
            unicode = true;
            break;

        case 'y':
            dy = std::strtol(::optarg, 0, 0);
            break;

        default:
            usage(std::cerr, argv[0]);
            return EXIT_FAILURE;
        }
    }

    std::string text;
    std::wstring wtext;

    if (::optind == argc) {
        if (unicode)
            std::wcin >> wtext;
        else
            std::cin >> text;
    } else if (!unicode) {
        text = argv[::optind];
    } else {
        usage(std::cerr, argv[0]);
        return EXIT_FAILURE;
    }

    if (ptsize != f.size()) {
        f.resize(ptsize);
    }

    std::cout << "Family: " << (f.family() ? f.family() : "n/a") << "\n"
              << "Style: " << (f.style() ? f.style() : "n/a") << "\n"
              << "Size: " << f.size() << "\n"
              << "Height: " << f.height() << "\n"
              << "Ascent: " << f.ascent() << "\n"
              << "Descent: " << f.descent() << "\n"
              << "Leading: " << f.leading() << "\n"
        ;

    size2d size = unicode ? f.size(wtext) : f.size(text);
    std::cout << "Text size: " << size.width << 'x' << size.height << std::endl;

    std::ostringstream os;
    if (f.family()) {
        os << f.family();
        if (f.style()) {
            os << " - " << f.style();
        }
    } else {
        os << "SDL Font View";
    }

    window win(os.str(), size);
    color bg = make_rgb(0xff);
    color fg = make_rgb(0x00);

    canvas c = unicode ? f.render(wtext, fg, bg) : f.render(text, fg, bg);

    if (use_canvas) {
        win.view().blit(c);
    } else {
        win.view().fill(bg);
        if (unicode) {
            f.draw(win.view(), wtext, fg, 0, f.ascent() + dy);
        } else {
            f.draw(win.view(), text, fg, 0, f.ascent() + dy);
        }
    }
    
    win.update();

    while (event* pe = win.events().wait()) {
        switch (pe->type()) {
        case event::redraw:
            if (use_canvas) {
                win.view().blit(c, win.size());
            } else {
                win.view().fill(bg);
                if (unicode) {
                    f.draw(win.view(), wtext, fg, 0, f.ascent() + dy);
                } else {
                    f.draw(win.view(), text, fg, 0, f.ascent() + dy);
                }
            }
            win.update();
            break;

        case event::keydown:
            switch (dynamic_cast<keyboard_event*>(pe)->key()) {
            case 'Q':
            case '\033':
                win.close();
            }
            break;
        }
    }

    return EXIT_SUCCESS;
}
