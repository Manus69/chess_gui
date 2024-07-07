#include "_private.h"

static bool _is_promotion(int from, int to, CLR clr)
{
    static const int _prows[CLR_COUNT] =
    {
        [CLR_W] = 0,
        [CLR_B] = SIDE - 1,
    };

    (void) from;

    return _idx_row(to) == _prows[clr];
}

static void _apply_pawn_move(Pos * pos, int from, int to, CLR clr)
{
    if (_is_promotion(from, to, clr))
    {
        Brd_set(& pos->brd, from, '_');
        Brd_set(& pos->brd, to, QUEEN_CSTR[clr]);

        return ;
    }

    Brd_move(& pos->brd, from, to);
}

static bool _is_lc(int from, int to)
{
    return _idx_col(from) - _idx_col(to) == 2;
}

static bool _is_rc(int from, int to)
{
    return _idx_col(from) - _idx_col(to) == -2;
}

static void _apply_castle(Pos * pos, int from, int to, int rook_from, int rook_to)
{
    Brd_move(& pos->brd, from, to);
    Brd_move(& pos->brd, rook_from, rook_to);
}

static void _apply_king_move(Pos * pos, int from, int to, CLR clr)
{
    pos->king_idx[clr] = to;
    pos->cstl_data[clr].king_moved = true;

    if (_is_lc(from, to))
    {
        return _apply_castle(pos, from, to, _row_col_idx(_idx_row(from), 0), _row_col_idx(_idx_row(from), _idx_col(from) - 1));
    }
    if (_is_rc(from, to))
    {
        return _apply_castle(pos, from, to, _row_col_idx(_idx_row(from), SIDE - 1), _row_col_idx(_idx_row(from), _idx_col(from) + 1));
    }

    Brd_move(& pos->brd, from, to);
}

void Pos_apply_move(Pos * pos, int from, int to)
{
    char x;

    pos->last_move.a = from;
    pos->last_move.b = to;
    pos->move_clr = _clr_invert(pos->move_clr);

    x = * Brd_get(& pos->brd, from);

    if (_piece_pawn(x)) return _apply_pawn_move(pos, from, to, _piece_clr(x));
    if (_piece_king(x)) return _apply_king_move(pos, from, to, _piece_clr(x));

    Brd_move(& pos->brd, from, to);
}