# Mission Statement #

**jacui** is intended to be a simple, lightweight, cross-platform, "modern" C++ user interface library.

When it's finished, I mean.

Currently, it's just a simple C++ wrapper for the SDL (Simple DirectMedia Layer) on Linux and Windows.

# News #

## 2011-05-14: **jacui** 0.2.2 released ##

Bugfix release. Also contains some basic Doxygen documentation.

# Drawing Sample #

A complete simple drawing program using a custom image brush:

```
#include "jacui/image.hpp"
#include "jacui/window.hpp"

int main(int argc, char* argv[])
{
    using namespace jacui;

    window w("jacui drawing sample");
    image brush("brush.png");

    while (event* pe = w.events().wait()) {
        if (pe->type() == event::mousedown || pe->type() == event::mousemove) {
            mouse_event* pme = dynamic_cast<mouse_event*>(pe);
            if (pme->button() == mouse_event::lbutton) {
                w.view().blit(brush, pme->point());
                w.update();
            }
        }
    }

    return 0;
}
```