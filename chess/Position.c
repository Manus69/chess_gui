#include "_private.h"

Position Position_init(Board board, Move last_move, byte ci_white, byte ci_black)
{
    Position pos;

    pos.board = board;
    pos.last_move = last_move;
    pos.castle_info[CLR_WHITE] = ci_white;
    pos.castle_info[CLR_BALCK] = ci_black;

    return pos;
}

Position Position_init_from_cstr(const char * cstr, Move last_move, byte ci_white, byte ci_black)
{
    Board board;

    board = Board_init_cstr(cstr);

    return Position_init(board, last_move, ci_white, ci_black);
}

Position Position_init_default(void)
{
    return Position_init_from_cstr(Chess_default_pos_cstr(), Move_init_no_move(), castle_info_default(), castle_info_default());
}