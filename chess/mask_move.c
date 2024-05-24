#include "_private.h"

static bool _check_after_move(const Position * pos, int from, int to, const BrdInfo * info)
{
    Board   next;
    CLR     clr;
    int     king_idx;

    next = Board_move_copy(& pos->board, from, to);
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
    int from, to;

    from = _row_col_idx(row, col);

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

static void _mask_castle(u64 * mask, const Position * pos, int row, int col, const BrdInfo * info)
{
    CLR clr;

    (void) info;
    clr = Board_square_piece_clr(& pos->board, _row_col_idx(row, col));

    if (castle_info_can_castle_short(pos->castle_info[clr]))
    {
        if (! Board_square_empty(& pos->board, _row_col_idx(row, col + 1)))                         return ;
        if (! Board_square_empty(& pos->board, _row_col_idx(row, col + 2)))                         return ;
        if (Board_square_attacked_by(& pos->board, _row_col_idx(row, col + 1), CLR_invert(clr)))    return ;
        if (Board_square_attacked_by(& pos->board, _row_col_idx(row, col + 2), CLR_invert(clr)))    return ;

        u64_set_bit(mask, _row_col_idx(row, col + 2));
    }

    if (castle_info_can_castle_long(pos->castle_info[clr]))
    {
        if (! Board_square_empty(& pos->board, _row_col_idx(row, col - 1)))                         return ;
        if (! Board_square_empty(& pos->board, _row_col_idx(row, col - 2)))                         return ;
        if (Board_square_attacked_by(& pos->board, _row_col_idx(row, col - 1), CLR_invert(clr)))    return ;
        if (Board_square_attacked_by(& pos->board, _row_col_idx(row, col - 2), CLR_invert(clr)))    return ;

        u64_set_bit(mask, _row_col_idx(row, col - 2));
    }
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

    _mask_castle(& mask, pos, row, col, info);

    return mask;
}

static void _mask_pawn_dir(u64 * mask, const Position * pos, int row, int col, int drow, const BrdInfo * info)
{
    if (! Board_square_empty(& pos->board, _row_col_idx(row + drow, col)))                   return ;
    if (_check_after_move(pos, _row_col_idx(row, col), _row_col_idx(row + drow, col), info)) return ;

    u64_set_bit(mask, _row_col_idx(row + drow, col));
}

static void _mask_pawn_initial(u64 * mask, const Position * pos, int row, int col, int drow, const BrdInfo * info)
{
    _mask_pawn_dir(mask, pos, row, col, drow, info);
    if (* mask) _mask_pawn_dir(mask, pos, row + drow, col, drow, info);
}

static bool _last_move_pawn_initial(const Position * pos, int row, int col, int drow, int dcol)
{
    (void) drow;

    if (! Move_valid(pos->last_move))                                           return false;
    if (! piece_pawn(Board_at(& pos->board, pos->last_move.to)))                return false;
    if (abs_(_idx_row(pos->last_move.to) - _idx_row(pos->last_move.from)) != 2) return false;
    
    return _row_col_idx(row, col + dcol) == pos->last_move.to;
}

static void _mask_pawn_en_passant(u64 * mask, const Position * pos, int row, int col, int drow, int dcol, const BrdInfo * info)
{
    (void) info;

    if (_last_move_pawn_initial(pos, row, col, drow, dcol)) u64_set_bit(mask, _row_col_idx(row + drow, col + dcol));
}

static void _mask_pawn_capture_dir(u64 * mask, const Position * pos, int row, int col, int drow, int dcol, const BrdInfo * info)
{
    int from, to;

    from = _row_col_idx(row, col);
    to = _row_col_idx(row + drow, col + dcol);

    if (! _row_col_valid(row + drow, col + dcol))               return ;
    if (Board_square_empty(& pos->board, to))                   return _mask_pawn_en_passant(mask, pos, row, col, drow, dcol, info);
    if (! Board_square_piece_same_clr(& pos->board, from, to))  u64_set_bit(mask, _row_col_idx(row + drow, col + dcol));
}

static u64 _mask_move_pawn(const Position * pos, int row, int col, const BrdInfo * info)
{
    u64 mask = 0;
    CLR clr;

    clr = Board_square_piece_clr(& pos->board, _row_col_idx(row, col));

    if (clr == CLR_WHITE)
    {
        if (row == CHESS_BOARD_SIDE - 2)    _mask_pawn_initial(& mask, pos, row, col, -1, info);
        else                                _mask_pawn_dir(& mask, pos, row, col, -1, info);

        _mask_pawn_capture_dir(& mask, pos, row, col, -1, -1, info);
        _mask_pawn_capture_dir(& mask, pos, row, col, -1, 1, info);
    }
    else
    {
        if (row == 1)                       _mask_pawn_initial(& mask, pos, row, col, 1, info);
        else                                _mask_pawn_dir(& mask, pos, row, col, 1, info);

        _mask_pawn_capture_dir(& mask, pos, row, col, 1, -1, info);
        _mask_pawn_capture_dir(& mask, pos, row, col, 1, 1, info);
    }

    return mask;
}

u64 mask_move_mask_info(const Position * pos, int idx, const BrdInfo * info)
{
    int     row;
    int     col;
    char    piece;

    row = _idx_row(idx);
    col = _idx_col(idx);
    piece = Board_at(& pos->board, idx);

    if (piece_pawn(piece))      return _mask_move_pawn(pos, row, col, info);
    if (piece_king(piece))      return _mask_move_king(pos, row, col, info);
    if (piece_knight(piece))    return _mask_move_knight(pos, row, col, info);
    if (piece_bishop(piece))    return _mask_move_bishop(pos, row, col, info);
    if (piece_rook(piece))      return _mask_move_rook(pos, row, col, info);
    if (piece_queen(piece))     return _mask_move_queen(pos, row, col, info);

    return 0;
}

u64 mask_move_mask(const Position * pos, int idx)
{
    BrdInfo info;

    info = BrdInfo_init(& pos->board);

    return mask_move_mask_info(pos, idx, & info);
}