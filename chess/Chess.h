#ifndef CHESS_H
#define CHESS_H

#include "../src/common.h"

typedef enum CHESS_PIECE CHESS_PIECE;

enum CHESS_PIECE
{
    CHESS_PIECE_NONE = '_',
    CHESS_PIECE_WK = 'K',
    CHESS_PIECE_BK = 'k',
    CHESS_PIECE_WQ = 'Q',
    CHESS_PIECE_BQ = 'q',
    CHESS_PIECE_WB = 'B',
    CHESS_PIECE_BB = 'b',
    CHESS_PIECE_WN = 'N',
    CHESS_PIECE_BN = 'n',
    CHESS_PIECE_WR = 'R',
    CHESS_PIECE_BR = 'r',
    CHESS_PIECE_WP = 'P',
    CHESS_PIECE_BP = 'p',
};

typedef struct Chess Chess;

void    Chess_init_from_Pos_cstr(Chess * chess, const char * cstr);
Chess * Chess_new_game(void);
void    Chess_del(Chess * chess);
char *  Chess_get_board_cstr(const Chess * chess);
bool    Chess_try_move(Chess * chess, Move mv);
void    Chess_dbg(const Chess * chess);

#endif