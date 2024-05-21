#include "_private.h"

#define WW 1000
#define WH 1000

static void _window(Layout * layout, int ww, int wh)
{
    layout->window = (Rectangle)
    {
        .width = ww,
        .height = wh,
    };
}

static void _board(Layout * layout)
{
    float min;
    float offset;
    float size;

    min = min_(layout->window.width, layout->window.height);
    offset = min / 10;
    size = min - 2 * offset;
    
    layout->board = Board_init(offset, offset, size);
}

Layout Layout_default(int ww, int wh)
{
    Layout layout = {};

    _window(& layout, ww, wh);
    _board(& layout);

    return layout;
}