#include "_private.h"

bool mask_includes(u64 mask, int idx)
{
    return u64_bit(mask, idx);
}

static u64 _mask_row_col(int row, int col)
{
    u64 mask = 0;

    if (_row_col_valid(row, col)) u64_set_bit(& mask, _row_col_idx(row, col));

    return mask;
}

static bool _mask_attack_add(u64 * mask, int row, int col)
{
    int idx;

    if (_row_col_valid(row, col))
    {
        idx = _row_col_idx(row, col);
        
        return u64_set_bit(mask, idx);
    }

    return false;
}

static bool _mask_attack_add_collision_check(u64 * mask, const Board * board, int row, int col)
{
    return _mask_attack_add(mask, row, col) && Board_square_is(board, _row_col_idx(row, col), CHESS_PIECE_NONE);
}

static u64 _mask_attack_dir(const Board * board, int row, int col, int row_inc, int col_inc)
{
    u64 mask = 0;

    while (true)
    {
        row += row_inc;
        col += col_inc;

        if (! _mask_attack_add_collision_check(& mask, board, row, col)) break;
    }

    return mask;
}

u64 mask_attack_pawn_up(int row, int col)
{
    return _mask_row_col(row - 1, col - 1) | _mask_row_col(row - 1, col + 1);
}

u64 mask_attack_pawn_down(int row, int col)
{
    return _mask_row_col(row + 1, col - 1) | _mask_row_col(row + 1, col + 1);   
}

u64 mask_attack_king(int row, int col)
{
    return _mask_row_col(row - 1, col - 1) | _mask_row_col(row - 1, col) | _mask_row_col(row - 1, col + 1) |
            _mask_row_col(row, col - 1) | _mask_row_col(row, col + 1) |
            _mask_row_col(row + 1, col - 1) | _mask_row_col(row + 1, col) | _mask_row_col(row + 1, col + 1);
}

u64 mask_attack_knight(int row, int col)
{
    return _mask_row_col(row - 2, col - 1) | _mask_row_col(row - 2, col + 1) |
            _mask_row_col(row - 1, col - 2) | _mask_row_col(row - 1, col + 2) |
            _mask_row_col(row + 1, col - 2) | _mask_row_col(row + 1, col + 2) |
            _mask_row_col(row + 2, col - 1) | _mask_row_col(row + 2, col + 1);
}

u64 mask_attack_bishop(const Board * board, int row, int col)
{
    return _mask_attack_dir(board, row, col, -1, -1) | _mask_attack_dir(board, row, col, 1, 1) |
            _mask_attack_dir(board, row, col, -1, 1) | _mask_attack_dir(board, row, col, 1, -1);
}

u64 mask_attack_rook(const Board * board, int row, int col)
{
    return _mask_attack_dir(board, row, col, -1, 0) | _mask_attack_dir(board, row, col, 1, 0) |
            _mask_attack_dir(board, row, col, 0, -1) | _mask_attack_dir(board, row, col, 0, 1);
}

u64 mask_attack_queen(const Board * board, int row, int col)
{
    return mask_attack_bishop(board, row, col) | mask_attack_rook(board, row, col);
}

u64 mask_attack_mask(const Board * board, int idx)
{
    int     row;
    int     col;
    char    piece;

    row = _idx_row(idx);
    col = _idx_col(idx);
    piece = Board_at(board, idx);

    if (piece_pawn_white(piece))    return mask_attack_pawn_up(row, col);
    if (piece_pawn_black(piece))    return mask_attack_pawn_down(row, col);
    if (piece_king(piece))          return mask_attack_king(row, col);
    if (piece_knight(piece))        return mask_attack_knight(row, col);
    if (piece_bishop(piece))        return mask_attack_bishop(board, row, col);
    if (piece_rook(piece))          return mask_attack_rook(board, row, col);
    if (piece_queen(piece))         return mask_attack_queen(board, row, col);

    return 0;
}
