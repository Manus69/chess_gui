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

typedef struct  Board    Board;
typedef struct  Position Position;
typedef struct  PosInfo  PosInfo;
typedef enum    CLR      CLR;

enum CLR
{
    CLR_WHITE,
    CLR_BALCK,
    CLR_NONE,
};

struct Board
{
    char squares[CHESS_BOARD_SIZE];
};

struct Position
{
    Board   board;
    Move    last_move;
    byte    castle_info[CLR_NONE];
};

struct PosInfo
{
    u64     attack_mask[CLR_NONE];
    char    king_idx[CLR_NONE];
    char    material[CLR_NONE];
};

CLR piece_clr(char p);
bool piece_none(char p);
bool piece_king(char p);
bool piece_queen(char p);
bool piece_bishop(char p);
bool piece_knight(char p);
bool piece_rook(char p);
bool piece_pawn(char p);
char piece_value(char p);

u64 mask_attack_mask(const Board * board, int idx);

Board Board_init_empty(void);
Board Board_init_cstr(const char * cstr);
Board Board_init_copy(const Board * board);
char * Board_get(Board * board, int idx);
char Board_at(const Board * board, int idx);
void Board_set(Board * board, int idx, char piece);
bool Board_is_square(const Board * board, int idx, char piece);
void Board_move(Board * board, int from, int to);
void Board_move_Move(Board * board, Move mv);
u64 Board_hash(const Board * board);

byte castle_info_default(void);
void castle_info_move_king(byte * ci);
void castle_info_move_rooka(byte * ci);
void castle_info_move_rookh(byte * ci);
bool castle_info_can_castle_short(byte ci);
bool castle_info_can_castle_long(byte ci);

Position Position_init(Board board, Move last_move, byte ci_white, byte ci_black);
Position Position_init_from_cstr(const char * cstr, Move last_move, byte ci_white, byte ci_black);
Position Position_init_default(void);

PosInfo PosInfo_init(const Position * position);

#endif