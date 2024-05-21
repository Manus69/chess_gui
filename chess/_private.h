#ifndef _PRIVATE_H
#define _PRIVATE_H

#include "Chess.h"
#include <string.h>

#define CHESS_BOARD_SIDE COMMON_BOARD_SIDE
#define CHESS_BOARD_SIZE COMMON_BOARD_SIZE
#define CHESS_POS_DFLT \
"rnbqkbnr" \
"pppppppp" \
"________" \
"________" \
"________" \
"________" \
"PPPPPPPP" \
"RNBQKBNR"

typedef struct Board    Board;
typedef struct KRInfo   KRInfo;

struct Board
{
    char squares[CHESS_BOARD_SIZE];
};

struct KRInfo
{
    char king_idx;
    bool rook_a_moved;
    bool rook_h_moved;
};

struct Position
{
    Board   board;
    KRInfo  white_kr;
    KRInfo  black_kr;
};

Board Board_init_empty(void);
Board Board_init_cstr(const char * cstr);
Board Board_init_copy(const Board * board);
char * Board_get(Board * board, int idx);
char Board_at(const Board * board, int idx);
void Board_set(Board * board, int idx, char piece);
bool Board_is_square(const Board * board, int idx, char piece);
void Board_move(Board * board, int from, int to);
u64 Board_hash(const Board * board);

#endif