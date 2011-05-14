#include "jacui/canvas.hpp"

int main(int argc, char *argv[])
{
    using namespace jacui;

    canvas c1(0, 0);
    canvas c2(100, 100);

    c2.blit(c1);
    c2.blit(c1, point2d(0, 0));
    c2.blit(c1, rect2d(0, 0, 0, 0));
    c2.blit(c1, rect2d(0, 0, 100, 100));
    c2.blit(c1, rect2d(0, 0, 200, 200));

    c2.blit(c1, rect2d(0, 0, 0, 0), point2d(0, 0));
    c2.blit(c1, rect2d(0, 0, 100, 100), rect2d(0, 0, 0, 0));

    return 0;
}
