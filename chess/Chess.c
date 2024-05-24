#include "_private.h"

Chess * Chess_new_game(void)
{
    Chess * chess;

    if (! (chess = calloc(1, sizeof(Chess)))) return NULL;

    chess->position = Position_init_default();
    chess->move_number = 0;

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
    BrdInfo info;

    info = BrdInfo_init(& chess->position);
    dbg_BrdInfo(& info);
}