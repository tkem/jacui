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

#include "bitstream_vera.hpp"
#include "jacui/window.hpp"
#include "jacui/cursors.hpp"
#include "jacui/image.hpp"
#include "jacui/font.hpp"

#include <algorithm>
#include <iostream>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <clocale>
#include <cassert>

#ifdef WIN32
// minimal getopt(3) implementation to work on Windows, too
char* optarg = 0;
int optind = 1;

int getopt(int argc, char* const argv[], const char* optstring)
{
    std::string opts(optstring);

    if (optind >= argc)
        return -1;
    if (*argv[optind] != '-')
        return -1;

    char opt = argv[optind++][1];
    std::string::size_type n = opts.find(opt);

    if (n == std::string::npos)
        return '?';
    if (n < opts.length() - 1 && opts[n + 1] == ':')
        optarg = argv[optind++];
    else
        optarg = 0;
    return opt;
}
#else
#include <getopt.h>
#endif

using namespace jacui;

class test_event: public user_event {
public:
    void cancel() { }

    const char* name() const { return "test"; }

    std::time_t time() const { return std::time(0); }
};

struct key_info { 
    keyboard_event::key_type key;
    const char* name;
} keys[] = {
    keyboard_event::bs, "BACKSPACE",
    keyboard_event::ht, "TAB",
    keyboard_event::cr, "ENTER",
    keyboard_event::esc, "ESCAPE",
    keyboard_event::del, "DELETE",

    keyboard_event::up, "UP",
    keyboard_event::down, "DOWN",
    keyboard_event::left, "LEFT",
    keyboard_event::right, "RIGHT",
    keyboard_event::pgup, "PAGE_UP",
    keyboard_event::pgdown, "PAGE_DOWN",
    keyboard_event::home, "HOME",
    keyboard_event::end, "END",
    keyboard_event::ins, "INS",

    keyboard_event::lshift, "LEFT_SHIFT",
    keyboard_event::rshift, "RIGHT_SHIFT",
    keyboard_event::lctrl, "LEFT_CTRL",
    keyboard_event::rctrl, "RIGHT_CTRL",
    keyboard_event::lalt, "LEFT_ALT",
    keyboard_event::ralt, "RIGHT_ALT",

    keyboard_event::f1, "F1",
    keyboard_event::f2, "F2",
    keyboard_event::f3, "F3",
    keyboard_event::f4, "F4",
    keyboard_event::f5, "F5",
    keyboard_event::f6, "F6",
    keyboard_event::f7, "F7",
    keyboard_event::f8, "F8",
    keyboard_event::f9, "F9",
    keyboard_event::f10, "F10",
    keyboard_event::f11, "F11",
    keyboard_event::f12, "F12",

    0, 0
};

const char* get_key(keyboard_event::key_type k)
{
    for (key_info* p = keys; p->key != 0; ++p) {
        if (p->key == k) {
            return p->name;
        }
    }

    return 0;
}

void output(std::ostream& os, const input_event& e)
{
    if (e.shift())
        os << "SHIFT-";
    if (e.ctrl())
        os << "CTRL-";
    if (e.alt())
        os << "ALT-";
}

void output(std::ostream& os, const char* msg, const test_event& e)
{
    os << msg << e.time();
}

void output(std::ostream& os, const char* msg, const redraw_event& e)
{
    os << msg << e.rect().x << ", " << e.rect().y << ", " 
       << e.rect().width << "x" << e.rect().height;
}

void output(std::ostream& os, const char* msg, const resize_event& e)
{
    os << msg << e.size().width << "x" << e.size().height;
}

void output(std::ostream& os, const char* msg, const mouse_event& e)
{
    os << msg;
    if (e.button()) {
        output(os, static_cast<const input_event&>(e));
        os << "BUTTON #" << e.button();
        if (e.button() == mouse_event::lbutton)
            os << " (left)";
        else if (e.button() == mouse_event::mbutton)
            os << " (middle)";
        else if (e.button() == mouse_event::rbutton)
            os << " (right)";
        os << " ";
    }
    os << "(" << e.point().x << ", " << e.point().y << ")";
}

void output(std::ostream& os, const char* msg, const keyboard_event& e)
{
    os << msg;
    output(os, static_cast<const input_event&>(e));

    if (e.key() == ' ') {
        os << "SPACE";
    } else if (std::isprint(e.key())) {
        os << char(e.key());
    } else if (get_key(e.key())) {
        os << get_key(e.key());
    } else {
        os << std::oct << '\\' << e.key() << std::dec;
    }

    if (e.wchar() >= 32) {
        os << " [U#" << std::hex << int(e.wchar()) << std::dec;

        char buf[32];
        wchar_t src[] = { e.wchar(), L'\0' };
        std::size_t n = std::wcstombs(buf, src, sizeof buf);
        if (n > 0 && n < sizeof buf - 1) {
            os << " '" << buf << "'";
        }

        os << "]";
    }
}

void output(std::ostream& os, const char* msg, const timer_event& e)
{
    os << msg << e.timer();
}

void output(std::ostream& os, const window& s, const event& e)
{
    os << e.name() << " event on " << &s << " [" << s.width() << "x" << s.height() << "]";

    switch (e.type()) {
    case event::redraw:
        output(os, ": ", dynamic_cast<const redraw_event&>(e));
        break;

    case event::resize:
        output(os, ": ", dynamic_cast<const resize_event&>(e));
        break;

    case event::mousemove:
    case event::mousedown:
    case event::mouseup:
        output(os, ": ", dynamic_cast<const mouse_event&>(e));
        break;

    case event::keydown:
    case event::keyup:
        output(os, ": ", dynamic_cast<const keyboard_event&>(e));
        break;

    case event::timer:
        output(os, ": ", dynamic_cast<const timer_event&>(e));
        break;

    case event::user:
        output(os, ": ", dynamic_cast<const test_event&>(e));
        break;

    default:
        break;
    }

    os << std::endl;
}

rect2d make_centered(point2d p, size2d img, size2d scr)
{
    rect2d r(0, 0, img.width, img.height);

    if (img.width > scr.width) {
        if (p.x > img.width - scr.width / 2)
            r.x = img.width - scr.width;
        else if (p.x > scr.width / 2)
            r.x = p.x - scr.width / 2;
        r.width = scr.width;
    }

    if (img.height > scr.height) {
        if (p.y > img.height - scr.height / 2)
            r.y = img.height - scr.height;
        else if (p.y > scr.height / 2)
            r.y = p.y - scr.height / 2;
        r.height = scr.height;
    }

    return r;
}

void draw(surface& s, const font& f, const char* text)
{
    size2d txtsz = f.size(text);

    int x = s.width() - txtsz.width - 8;
    int y = s.height() - 8;

    f.draw(s, text, make_rgb(0xff0000), x, y);
}

std::string filename(const std::string& path)
{
    std::string::size_type n = path.find_last_of(":\\/");
    return n != std::string::npos ? path.substr(n + 1) : path;
}

void update(window& win, const image& img, const font& f, const char* path)
{
    win.caption(filename(path));
    win.view().blit(img, win.size());
    draw(win.view(), f, path);
    win.update();
}

void update(window& win, const image& img, const font& f, const char* path, point2d p)
{
    size2d winsz = win.size();
    size2d imgsz = img.size();

    std::size_t x = p.x * imgsz.width / winsz.width;
    std::size_t y = p.y * imgsz.height / winsz.height;

    win.caption(filename(path));
    if (win.width() > img.width() || win.height() > img.height()) {
        win.view().fill(make_rgb(0));
    }
    win.view().blit(img, make_centered(point2d(x, y), imgsz, winsz), point2d());
    draw(win.view(), f, path);
    win.update();
}

void usage(std::ostream& os, const char* name) 
{
    os << "Usage: " << name << " [ OPTION ] FILE ...\n"
       << "Options:\n"
       << "  -f               fullscreen mode\n"
       << "  -h HEIGHT        window height in pixels\n"
       << "  -i INTERVAL      slide show interval in msec\n"
       << "  -n               no resize\n"
       << "  -v               verbose output\n"
       << "  -w WIDTH         window width in pixels\n"
       << "\n"
       << "Actions:\n"
       << "  SPACE, 'N':      next image\n"
       << "  BACKSPACE, 'P':  previous image\n"
       << "  ESC, 'Q':        quit\n"
       << std::endl;
}

int main(int argc, char* argv[])
{
    std::setlocale(LC_CTYPE, "");

    std::size_t width = 0;
    std::size_t height = 0;
    window::flags_type flags = 0;
    unsigned long interval = 0;
    bool verbose = false;

    // parse command line options
    for (int c; (c = ::getopt(argc, argv, "fh:i:nvw:")) > 0; ) {
        switch(c) {
        case 'f':
            flags |= window::fullscreen;
            break;

        case 'h':
            height = std::strtoul(::optarg, 0, 0);
            break;

        case 'i':
            interval = std::strtoul(::optarg, 0, 0);
            break;

        case 'n':
            flags |= window::noresize;
            break;

        case 'v':
            verbose = true;
            break;

        case 'w':
            width = std::strtoul(::optarg, 0, 0);
            break;

        default:
            usage(std::cerr, argv[0]);
            return EXIT_FAILURE;
        }
    }

    if (::optind == argc) {
        usage(std::cerr, argv[0]);
        return EXIT_FAILURE;
    }

    int index = ::optind;
    bool zoom = false;
    point2d pos;

    image img(argv[index]);
    font fnt(bitstream_vera_ttf, sizeof bitstream_vera_ttf, 12);
    window win(filename(argv[index]), width, height, flags);
    win.cursor(cursors::crosshair());

    update(win, img, fnt, argv[index]);

    window::timer_type timer = interval ? win.events().set_interval(interval) : 0;

    test_event tevent;

    std::cerr << "starting event loop...\n";
    while (event* pe = win.events().wait()) {
        if (verbose)
            output(std::cerr, win, *pe);

        mouse_event* me = 0;
        keyboard_event* ke = 0;
        std::string input;

        switch (pe->type()) {
        case event::redraw:
            if (zoom) {
                update(win, img, fnt, argv[index], pos);
            } else {
                update(win, img, fnt, argv[index]);
            }
            break;

        case event::mousedown:
            me = dynamic_cast<mouse_event*>(pe);
            assert(me);

            if ((zoom = !zoom)) {
                update(win, img, fnt, argv[index], pos = me->point());
            } else {
                update(win, img, fnt, argv[index]);
            }

            break;

        case event::keydown:
            ke = dynamic_cast<keyboard_event*>(pe);
            assert(ke);

            if (timer) {
                if (verbose)
                    std::cerr << "clearing timer " << timer << "...\n";
                if (!win.events().clear_timer(timer))
                    std::cerr << "clearing timer " << timer << " failed\n";
                timer = 0;
            } 

            if (ke->key() == ' ' || ke->key() == 'N') {
                if (++index == argc)
                    index = ::optind;
                img.load(argv[index]);
                update(win, img, fnt, argv[index]);
                zoom = false;
            } else if (ke->key() == keyboard_event::bs || ke->key() == 'P') {
                if (--index < :: optind)
                    index = argc -1;
                img.load(argv[index]);
                update(win, img, fnt, argv[index]);
                zoom = false;
            } else if (ke->key() == keyboard_event::ht) {
                win.resize(width, height);
                // programmatic resize does not trigger redraw event!
                update(win, img, fnt, argv[index]);
            } else if (ke->key() == keyboard_event::esc || ke->key() == 'Q') {
                win.close();
            }

            break;

        case event::quit:
            if (verbose) {
                std::cout << "Do you really want to quit (yes/no)?" << std::endl;
                std::cin >> input;
                
                if (input.empty() || std::toupper(input[0]) != 'Y') {
                    std::cerr << "cancelling quit event\n";
                    pe->cancel();
                }
            }
            break;

        case event::timer:
            if (!zoom) {
                if (++index == argc)
                    index = ::optind;
                img.load(argv[index]);
                update(win, img, fnt, argv[index]);
            }
            break;

        default:
            break;
        }
    }

    return EXIT_SUCCESS;
}
