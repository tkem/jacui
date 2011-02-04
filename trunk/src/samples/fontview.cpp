#include "icons.h"
#include "vera.h"

#include "jacui/window.h"
#include "jacui/event.h"
#include "jacui/font.h"
#include "jacui/colors.h"

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

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
    
    font f(vera_ttf, sizeof vera_ttf, 12);
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
            ptsize = boost::lexical_cast<float>(::optarg);
            break;

        case 'u':
            unicode = true;
            break;

        case 'y':
            dy = boost::lexical_cast<int>(::optarg);
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

    window win(os.str(), xpmicon(sdl_powered_32_xpm), size);
    color bg = unicode ? colors::silver : colors::white;
    color fg = colors::black;

    canvas c = unicode ? f.render(wtext, fg, bg) : f.render(text, fg, bg);

    if (use_canvas) {
        win.surface().blit(c);
    } else {
        win.surface().fill(bg);
        if (unicode) {
            f.draw(win.surface(), wtext, fg, 0, f.ascent() + dy);
        } else {
            f.draw(win.surface(), text, fg, 0, f.ascent() + dy);
        }
    }
    
    win.update();

    while (event* pe = win.wait()) {
        switch (pe->type()) {
        case event::redraw:
            if (use_canvas) {
                win.surface().blit(c, win.size());
            } else {
                win.surface().fill(bg);
                if (unicode) {
                    f.draw(win.surface(), wtext, fg, 0, f.ascent() + dy);
                } else {
                    f.draw(win.surface(), text, fg, 0, f.ascent() + dy);
                }
            }
            win.update();
            break;

        case event::keydown:
            switch (dynamic_cast<keyboard_event*>(pe)->key()) {
            case 'Q':
            case '\033':
                win.quit();
            }
            break;
        }
    }

    return EXIT_SUCCESS;
}
