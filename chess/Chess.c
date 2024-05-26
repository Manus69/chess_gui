#include "_private.h"

#include <stdio.h>

void Chess_init_from_Position(Chess * chess, Position pos, CLR to_move)
{
    chess->position = pos;
    chess->move_number = 0;
    chess->to_move = to_move;
}

void Chess_init_from_Pos_cstr(Chess * chess, const char * cstr)
{
    Position    pos;
    CLR         clr;

    pos = Position_init_cstr(cstr);
    clr = Position_to_move(& pos);

    return Chess_init_from_Position(chess, pos, clr);
}

Chess * Chess_new_game(void)
{
    Chess * chess;

    if (! (chess = calloc(1, sizeof(Chess)))) return NULL;

    Chess_init_from_Position(chess, Position_init_default(), CLR_WHITE);

    return chess;
}

void Chess_del(Chess * chess)
{
    free(chess);
}

char * Chess_get_board_cstr(const Chess * chess)
{
    return Position_Board_cstr(& chess->position);
}

void Chess_dbg(const Chess * chess)
{
    Str str;

    str = Position_to_Str(& chess->position);
    Str_dbg(& str);
    nl_;

    Str_del(& str);
}