#include "_private.h"

static bool _check_after_move(const Position * pos, int from, int to, const BrdInfo * info)
{
    Board   next;
    CLR     clr;
    int     king_idx;

    next = Board_move_copy(& pos, from, to);
    clr = Board_square_piece_clr(& next, to);
    king_idx = piece_king(Board_at(& next, to)) ? to : info->king_idx[clr];

    return Board_square_attacked_by(& next, king_idx, CLR_invert(clr));
}

static void _mask_if_legal(u64 * mask, const Position * pos, int from, int to_row, int to_col, const BrdInfo * info)
{
    if (! _row_col_valid(to_row, to_col)) return ;
    if (Board_square_piece_same_clr(& pos->board, from, _row_col_idx(to_row, to_col))) return ;
    if (! _check_after_move(pos, from, _row_col_idx(to_row, to_col), info)) u64_set_bit(mask, _row_col_idx(to_row, to_col));
}

static void _mask_dir(u64 * mask, const Position * pos, int row, int col, int drow, int dcol, const BrdInfo * info)
{
    int     from, to;
    CLR     clr;

    from = _row_col_idx(row, col);
    clr = Board_square_piece_clr(& pos->board, from);

    row += drow;
    col += dcol;

    while (_row_col_valid(row, col))
    {
        to = _row_col_idx(row, col);

        if (Board_square_piece_same_clr(& pos->board, from, to))    return ;
        if (! _check_after_move(pos, from, to, info))               u64_set_bit(mask, to);
        if (! Board_square_empty(& pos->board, to))                 return ;

        row += drow;
        col += dcol;
    }
}

static u64 _mask_move_rook(const Position * pos, int row, int col, const BrdInfo * info)
{
    u64 mask = 0;

    _mask_dir(& mask, pos, row, col, -1, 0, info);
    _mask_dir(& mask, pos, row, col, 1, 0, info);
    _mask_dir(& mask, pos, row, col, 0, -1, info);
    _mask_dir(& mask, pos, row, col, 0, 1, info);

    return mask;
}

static u64 _mask_move_bishop(const Position * pos, int row, int col, const BrdInfo * info)
{
    u64 mask = 0;

    _mask_dir(& mask, pos, row, col, -1, -1, info);
    _mask_dir(& mask, pos, row, col, 1, 1, info);
    _mask_dir(& mask, pos, row, col, 1, -1, info);
    _mask_dir(& mask, pos, row, col, -1, 1, info);

    return mask;
}

static u64 _mask_move_queen(const Position * pos, int row, int col, const BrdInfo * info)
{
    return _mask_move_rook(pos, row, col, info) | _mask_move_bishop(pos, row, col, info);
}

static u64 _mask_move_knight(const Position * pos, int row, int col, const BrdInfo * info)
{
    u64 mask = 0;
    int from;

    from = _row_col_idx(row, col);

    _mask_if_legal(& mask, pos, from, row - 2, col - 1, info);
    _mask_if_legal(& mask, pos, from, row - 2, col + 1, info);
    _mask_if_legal(& mask, pos, from, row - 1, col - 2, info);
    _mask_if_legal(& mask, pos, from, row - 1, col + 2, info);
    _mask_if_legal(& mask, pos, from, row + 1, col - 2, info);
    _mask_if_legal(& mask, pos, from, row + 1, col + 2, info);
    _mask_if_legal(& mask, pos, from, row + 2, col - 1, info);
    _mask_if_legal(& mask, pos, from, row + 2, col + 1, info);

    return mask;
}

static void _mask_castle(const Position * pos, int row, int col, const BrdInfo * info)
{
    
}

static u64 _mask_move_king(const Position * pos, int row, int col, const BrdInfo * info)
{
    u64 mask = 0;
    int from;

    from = _row_col_idx(row, col);

    _mask_if_legal(& mask, pos, from, row - 1, col - 1, info);
    _mask_if_legal(& mask, pos, from, row - 1, col, info);
    _mask_if_legal(& mask, pos, from, row - 1, col + 1, info);
    _mask_if_legal(& mask, pos, from, row, col - 1, info);
    _mask_if_legal(& mask, pos, from, row, col + 1, info);
    _mask_if_legal(& mask, pos, from, row + 1, col - 1, info);
    _mask_if_legal(& mask, pos, from, row + 1, col, info);
    _mask_if_legal(& mask, pos, from, row + 1, col + 1, info);
}

u64 mask_move_mask_info(const Position * pos, int idx, const BrdInfo * info)
{

}

u64 mask_move_mask(const Position * pos, int idx)
{

}