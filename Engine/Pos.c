#include "_private.h"

Pos Pos_init(Brd brd, CstlData wcd, CstlData bcd, CLR move)
{
    return (Pos)
    {
        .brd = brd,
        .cstl_data[CLR_W] = wcd,
        .cstl_data[CLR_B] = bcd,
        .move = move,
    };
}

bool Pos_init_cstr(Pos * pos, const char * cstr)
{
    Brd brd;

    brd = Brd_init_cstr(cstr);
    * pos = Pos_init(brd, (CstlData) {}, (CstlData) {}, CLR_W);

    return true;
}

char * Pos_get_cstr(const Pos * pos)
{
    return (char *) pos->brd.sqr;
}
