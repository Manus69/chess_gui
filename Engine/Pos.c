#include "_private.h"

Pos Pos_init(Brd brd, CstlData wcd, CstlData bcd, int_int last_move, CLR move_clr)
{
    return (Pos)
    {
        .brd = brd,
        .cstl_data[CLR_W] = wcd,
        .cstl_data[CLR_B] = bcd,
        .king_idx[CLR_W] = Brd_find_king(& brd, CLR_W),
        .king_idx[CLR_B] = Brd_find_king(& brd, CLR_B),
        .last_move = last_move,
        .move_clr = move_clr,
    };
}

Pos Pos_init_default(Brd brd)
{
    return Pos_init(brd, (CstlData){}, (CstlData){}, (int_int){NO_IDX, NO_IDX}, CLR_W);
}

char * Pos_Brd_cstr(const Pos * pos)
{
    return (char *) pos->brd.sqr;
}

CLR Pos_turn(const Pos * pos)
{
    return pos->move_clr;
}

bool Pos_in_check(const Pos * pos, CLR clr)
{
    int row, col;

    row = _idx_row(pos->king_idx[clr]);
    col = _idx_col(pos->king_idx[clr]);

    return Brd_attacked_rc(& pos->brd, row, col, _clr_invert(clr));
}

bool Pos_any_moves(const Pos * pos, CLR clr)
{
    for (int k = 0; k < BRD_SIZE; k ++)
    {
        if (Brd_is_CLR(& pos->brd, k, clr))
        {
            if (Pos_compute_mmask(pos, k)) return true;
        }
    }

    return false;
}

