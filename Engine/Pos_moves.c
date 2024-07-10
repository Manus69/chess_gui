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

static bool _in_check_after_move(const Pos * pos, int from, int to, CLR clr)
{
    Brd brd;

    brd = Brd_init_cstr(pos->brd.sqr);
    Brd_move(& brd, from, to);

    return Brd_attacked_rc(& brd, _idx_row(pos->king_idx[clr]), _idx_col(pos->king_idx[clr]), _clr_invert(clr));
}

static u64 _mask_square_no_check(const Pos * pos, int from, int row, int col, CLR clr)
{
    u64 x = 0;

    if (_row_col_valid(row, col) && (_piece_clr(* Brd_get_rc(& pos->brd, row, col)) != clr))
    {
        if (! _in_check_after_move(pos, from, _row_col_idx(row, col), clr))
        {
            bits_set_bit(& x, _row_col_idx(row, col));
        }
    }

    return x;
}

static u64 _mask_rc(const Pos * pos, int row, int col, CLR clr)
{
    if (! CstrData_rc_allowed(pos->cstl_data[clr])) return 0;
    
    if (! Brd_is_empty_rc(& pos->brd, row, col + 1) ||
        ! Brd_is_empty_rc(& pos->brd, row, col + 2))
    {
        return 0;
    }

    clr = _clr_invert(clr);
    if (Brd_attacked_rc(& pos->brd, row, col, clr) ||
        Brd_attacked_rc(& pos->brd, row, col + 1, clr) ||
        Brd_attacked_rc(& pos->brd, row, col + 2, clr))
    {
        return 0;
    }

    return bits_one(_row_col_idx(row, col + 2));
}

static u64 _mask_lc(const Pos * pos, int row, int col, CLR clr)
{
    if (! CstlData_lc_allowed(pos->cstl_data[clr])) return 0;

    if (! Brd_is_empty_rc(& pos->brd, row, col - 1) ||
        ! Brd_is_empty_rc(& pos->brd, row, col - 2) ||
        ! Brd_is_empty_rc(& pos->brd, row, col - 3))
    {
        return 0;
    }

    clr = _clr_invert(clr);
    if (Brd_attacked_rc(& pos->brd, row, col, clr) ||
        Brd_attacked_rc(& pos->brd, row, col - 1, clr) ||
        Brd_attacked_rc(& pos->brd, row, col - 2, clr))
    {
        return 0;
    }

    return bits_one(_row_col_idx(row, col - 2));
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
    
    moves |= _mask_lc(pos, row, col, clr);
    moves |= _mask_rc(pos, row, col, clr);

    return moves;
}

static u64 _knight_moves(const Pos * pos, int row, int col, CLR clr)
{
    int from;

    from = _row_col_idx(row, col);

    return  _mask_square_no_check(pos, from, row - 2, col - 1, clr) |
            _mask_square_no_check(pos, from, row - 2, col + 1, clr) |
            _mask_square_no_check(pos, from, row - 1, col - 2, clr) |
            _mask_square_no_check(pos, from, row - 1, col + 2, clr) |
            _mask_square_no_check(pos, from, row + 1, col - 2, clr) |
            _mask_square_no_check(pos, from, row + 1, col + 2, clr) |
            _mask_square_no_check(pos, from, row + 2, col - 1, clr) |
            _mask_square_no_check(pos, from, row + 2, col + 1, clr);
}

static u64 _mask_dir(const Pos * pos, int row, int col, CLR clr, int dr, int dc)
{
    u64 mask = 0;
    int from;
    CLR clr_current;

    from = _row_col_idx(row, col);
    row += dr;
    col += dc;

    while (_row_col_valid(row, col))
    {
        clr_current = _piece_clr(* Brd_get_rc(& pos->brd, row, col));

        if (clr_current == clr) break ;
        if (! _in_check_after_move(pos, from, _row_col_idx(row, col), clr))
        {
            bits_set_bit(& mask, _row_col_idx(row, col));
        }
        if (clr_current != CLR_COUNT) break ;

        row += dr;
        col += dc;
    }

    return mask;
}

static u64 _rook_moves(const Pos * pos, int row, int col, CLR clr)
{
    return  _mask_dir(pos, row, col, clr, -1, 0) |
            _mask_dir(pos, row, col, clr, 1, 0) |
            _mask_dir(pos, row, col, clr, 0, -1) |
            _mask_dir(pos, row, col, clr, 0, 1);
}

static u64 _bish_moves(const Pos * pos, int row, int col, CLR clr)
{
    return  _mask_dir(pos, row, col, clr, -1, -1) |
            _mask_dir(pos, row, col, clr, -1, 1) |
            _mask_dir(pos, row, col, clr, 1, 1) |
            _mask_dir(pos, row, col, clr, 1, -1);
}

static u64 _queen_moves(const Pos * pos, int row, int col, CLR clr)
{
    return _rook_moves(pos, row, col, clr) | _bish_moves(pos, row, col, clr);
}

static const int PAWN_ROW[] =
{
    [CLR_W] = SIDE - 2,
    [CLR_B] = 1,
};

static u64 _mask_pawn_reg1(const Pos * pos, int from, int row, int col, CLR clr, int dr)
{
    if (Brd_is_rc_checked(& pos->brd, row + dr, col, '_'))
    {
        if (! _in_check_after_move(pos, from, _row_col_idx(row + dr, col), clr))return bits_one(_row_col_idx(row + dr, col));
    }

    return 0;
}

static u64 _mask_pawn_reg2(const Pos * pos, int from, int row, int col, CLR clr, int dr)
{
    if (row == PAWN_ROW[clr])
    {
        if (Brd_is_rc(& pos->brd, row + dr, col, '_') &&
            Brd_is_rc(& pos->brd, row + 2 * dr, col, '_') &&
            ! _in_check_after_move(pos, from, _row_col_idx(row + 2 * dr, col), clr))
        {
            return bits_one(_row_col_idx(row + 2 * dr, col));
        }
    }

    return 0;
}

static u64 _mask_pawn_capture(const Pos * pos, int from, int row, int col, CLR clr, int dr)
{
    u64 mask = 0;

    if (! Brd_is_rc_checked(& pos->brd, row + dr, col - 1, '_')) mask |= _mask_square_no_check(pos, from, row + dr, col - 1, clr);
    if (! Brd_is_rc_checked(& pos->brd, row + dr, col + 1, '_')) mask |= _mask_square_no_check(pos, from, row + dr, col + 1, clr);

    return mask;
}

static u64 _pawn_moves(const Pos * pos, int row, int col, CLR clr)
{
    int from;

    from = _row_col_idx(row, col);

    if (clr == CLR_W)
    {
        return  _mask_pawn_reg1(pos, from, row, col, clr, -1) |
                _mask_pawn_reg2(pos, from, row, col, clr, -1) |
                _mask_pawn_capture(pos, from, row, col, clr, -1);
    }
    else
    {
        return  _mask_pawn_reg1(pos, from, row, col, clr, 1) |
                _mask_pawn_reg2(pos, from, row, col, clr, 1) |
                _mask_pawn_capture(pos, from, row, col, clr, 1);
    }
}

u64 Pos_compute_mmask(const Pos * pos, int idx)
{
    int     row, col;
    char    x;
    CLR     clr;

    x = * Brd_get(& pos->brd, idx);
    clr = _piece_clr(x);
    row = _idx_row(idx);
    col = _idx_col(idx);

    if (_piece_pawn(x))     return _pawn_moves(pos, row, col, clr);
    if (_piece_king(x))     return _king_moves(pos, row, col, clr);
    if (_piece_bish(x))     return _bish_moves(pos, row, col, clr);
    if (_piece_knight(x))   return _knight_moves(pos, row, col, clr);
    if (_piece_rook(x))     return _rook_moves(pos, row, col, clr);
    if (_piece_queen(x))    return _queen_moves(pos, row, col, clr);

    return 0;
}

bool Pos_try_move(const Pos * current, Pos * next, int from, int to)
{
    char    x;
    u64     mmask;

    if (! _idx_valid(from) || ! _idx_valid(to)) return false;

    mmask = Pos_compute_mmask(current, from);
    //
    dbg_mask(mmask);
    //

    x = * Brd_get(& current->brd, from);
    if (current->move_clr != _piece_clr(x)) return false;
    if (from == to)                         return false;
    if (! bits_bit(mmask, to))              return false;

    * next = * current;
    Pos_apply_move(next, from, to);

    return true;;
}