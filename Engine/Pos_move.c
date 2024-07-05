#include "_private.h"

static u64 _mask_square(const Pos * pos, int row, int col, CLR clr)
{
    u64 x = 0;

    if (! _row_col_valid(row, col))                             return 0;
    if (_piece_clr(* Brd_get_rc(& pos->brd, row, col)) == clr)  return 0;

    return bits_set_bit(& x, _row_col_idx(row, col));
}

static u64 _mask_square_not_attacked(const Pos * pos, int row, int col, CLR clr)
{
    return Brd_attacked_rc(& pos->brd, row, col, _clr_invert(clr)) ? 0 : _mask_square(pos, row, col, clr);
}

static bool _can_castle_left(const Pos * pos, int row, int col, CLR clr)
{
    if (CstlData_lc_allowed(pos->cstl_data[clr]))
    {
        return _mask_square_not_attacked(pos, row, col - 1, clr) && _mask_square_not_attacked(pos, row, col - 2, clr);
    }

    return false;
}

static bool _can_castle_right(const Pos * pos, int row, int col, CLR clr)
{
    if (CstrData_rc_allowed(pos->cstl_data[clr]))
    {
        return _mask_square_not_attacked(pos, row, col + 1, clr) && _mask_square_not_attacked(pos, row, col + 2, clr);
    }

    return false;
}

static u64 _king_moves(const Pos * pos, int row, int col, CLR clr)
{
    u64 moves;

    moves = _mask_square_not_attacked(pos, row - 1, col - 1, clr) |
            _mask_square_not_attacked(pos, row - 1, col, clr) |
            _mask_square_not_attacked(pos, row - 1, col + 1, clr) |
            _mask_square_not_attacked(pos, row, col - 1, clr) |
            _mask_square_not_attacked(pos, row, col + 1, clr) |
            _mask_square_not_attacked(pos, row + 1, col - 1, clr) |
            _mask_square_not_attacked(pos, row + 1, col, clr) |
            _mask_square_not_attacked(pos, row + 1, col + 1, clr);
    
    if (_can_castle_left(pos, row, col, clr))   bits_set_bit(& moves, _row_col_idx(row, col - 2));
    if (_can_castle_right(pos, row, col, clr))  bits_set_bit(& moves, _row_col_idx(row, col + 2));

    return moves;
}

u64 Pos_compute_moves(const Pos * pos, int idx)
{
    int     row, col;
    char    x;
    CLR     clr;

    x = * Brd_get(& pos->brd, idx);
    clr = _piece_clr(x);
    row = _idx_row(idx);
    col = _idx_col(idx);

    if (_piece_king(x)) return _king_moves(pos, row, col, clr);

    return 0;
}

bool Pos_move(const Pos * current, Pos * next, int from, int to)
{
    char    x;
    u64     moves;

    x = * Brd_get(& current->brd, from);
    if (current->move != _piece_clr(x)) return false;

    moves = Pos_compute_moves(current, from);
    //
    dbg_mask(moves);
    //

    return false;
}