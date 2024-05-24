#include "_private.h"

bool Chess_try_move(Chess * chess, Move mv)
{
    u64 mask;

    if (! Move_valid(mv)) return false;

    mask = mask_move_mask(& chess->position, mv.from);
    //
    dbg_mask(mask);
    //
    if (! mask_includes(mask, mv.to)) return false;

    chess->move_number ++;
    Position_apply_move(& chess->position, mv);

    return true;
}