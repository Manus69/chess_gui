#include "_private.h"

bool mask_includes(u64 mask, int idx)
{
    return u64_bit(mask, idx);
}

static bool _idx_valid(int idx)
{
    return idx >= 0 && idx < CHESS_BOARD_SIZE;
}

static bool _row_col_valid(int row, int col)
{
    return _idx_valid(_row_col_idx(row, col));
}

static u64 _mask_idx(int idx)
{
    u64 mask = 0;

    if (_idx_valid(idx)) u64_set_bit(& mask, idx);

    return mask;
}

static u64 _mask_row_col(int row, int col)
{
    return _mask_idx(_row_col_idx(row, col));
}

static bool _mask_add(u64 * mask, int row, int col)
{
    int idx;

    idx = _row_col_idx(row, col);
    if (_idx_valid(idx))
    {
        return u64_set_bit(mask, idx);
    }

    return false;
}

static bool _mask_add_collision_check(u64 * mask, const Board * board, int row, int col)
{
    return _mask_add(mask, row, col) && Board_is_square(board, _row_col_idx(row, col), CHESS_PIECE_NONE);
}

static u64 _mask_dir(const Board * board, int row, int col, int row_inc, int col_inc)
{
    u64 mask = 0;

    while (true)
    {
        row += row_inc;
        col += col_inc;

        if (! _mask_add_collision_check(& mask, board, row, col)) break;
    }

    return mask;
}

static u64 _mask_attack_pawn_up(int row, int col)
{
    
}

static u64 _mask_attack_pawn_down(int row, int col)
{
    
}

static u64 _mask_attack_king(int row, int col)
{

}

static u64 _mask_attack_knight(int row, int col)
{

}

u64 mask_attack_mask(const Board * board, int idx)
{

}