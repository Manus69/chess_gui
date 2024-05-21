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

char *  Chess_default_pos_cstr(void);

#endif