#include "_private.h"

bool Chess_try_move(Chess * chess, Move mv)
{
    u64 mask;

    if (! Move_valid(mv))                                                           return false;
    if (chess->to_move != Board_square_piece_clr(& chess->position.board, mv.from)) return false;

    mask = mask_move_mask(& chess->position, mv.from);
    //
    dbg_mask(mask);
    //
    if (! mask_includes(mask, mv.to)) return false;

    chess->move_number ++;
    chess->to_move = CLR_invert(chess->to_move);
    
    Position_apply_move(& chess->position, mv);

    return true;
}