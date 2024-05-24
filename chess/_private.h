#ifndef _PRIVATE_H
#define _PRIVATE_H

#include "Chess.h"
#include <string.h>
#include <stdlib.h>

#define CHESS_BOARD_SIDE COMMON_BOARD_SIDE
#define CHESS_BOARD_SIZE COMMON_BOARD_SIZE
#define CHESS_WK_INITIAL (CHESS_BOARD_SIZE - 4)
#define CHESS_BK_INITIAL (4)
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
typedef struct  BrdInfo  BrdInfo;
typedef enum    CLR      CLR;

enum CLR
{
    CLR_WHITE,
    CLR_BALCK,
    CLR_NONE,
};

static inline CLR CLR_invert(CLR clr)
{
    return ! clr;
}

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

struct BrdInfo
{
    u64     square_mask[CLR_NONE];
    // u64     attack_mask[CLR_NONE];
    char    king_idx[CLR_NONE];
    char    material[CLR_NONE];
};

struct Chess
{
    Position    position;
    CLR         to_move;
    int         move_number;
};

CLR piece_clr(char p);
bool piece_none(char p);
bool piece_king(char p);
bool piece_queen(char p);
bool piece_bishop(char p);
bool piece_knight(char p);
bool piece_rook(char p);
bool piece_pawn(char p);
bool piece_pawn_white(char p);
bool piece_pawn_black(char p);
bool piece_rook_or_queen(char p);
bool piece_bishop_or_queen(char p);
bool piece_white(char p);
bool piece_black(char p);
bool piece_king_clr(char p, CLR clr);
bool piece_queen_clr(char p, CLR clr);
bool piece_bishop_clr(char p, CLR clr);
bool piece_knight_clr(char p, CLR clr);
bool piece_rook_clr(char p, CLR clr);
bool piece_pawn_clr(char p, CLR clr);
char piece_value(char p);

//mask
bool mask_includes(u64 mask, int idx);
u64 mask_attack_mask(const Board * board, int idx);
u64 mask_attack_pawn_up(int row, int col);
u64 mask_attack_pawn_down(int row, int col);
u64 mask_attack_king(int row, int col);
u64 mask_attack_knight(int row, int col);
u64 mask_attack_bishop(const Board * board, int row, int col);
u64 mask_attack_rook(const Board * board, int row, int col);
u64 mask_attack_queen(const Board * board, int row, int col);

u64 mask_move_mask_info(const Position * pos, int idx, const BrdInfo * info);
u64 mask_move_mask(const Position * pos, int idx);

//board
Board Board_init_empty(void);
Board Board_init_cstr(const char * cstr);
Board Board_init_copy(const Board * board);
Board Board_move_copy(const Board * board, int from, int to);
char * Board_get(const Board * board, int idx);
char Board_at(const Board * board, int idx);
void Board_set(Board * board, int idx, char piece);
char Board_at_rc(const Board * board, int row, int col);
bool Board_square_isf(const Board * board, int row, int col, bool (* f)(char));
bool Board_square_is(const Board * board, int idx, char piece);
bool Board_square_empty(const Board * board, int idx);
bool Board_square_piece_same_clr(const Board * board, int lhs, int rhs);
bool Board_move_is_capture(const Board * board, Move mv);
CLR Board_square_piece_clr(const Board * board, int idx);
void Board_move(Board * board, int from, int to);
void Board_move_Move(Board * board, Move mv);
int Board_row_distance(int a_row, int b_row);
int Board_col_distance(int a_col, int b_col);
int Board_distance_row_col(int a_row, int a_col, int b_row, int b_col);
int Board_distance(int from, int to);
int Board_find_king(const Board * board, CLR clr);
u64 Board_hash(const Board * board);
bool Board_square_attacked_by(const Board * board, int idx, CLR clr);

byte castle_info_default(void);
void castle_info_move_king(byte * ci);
void castle_info_move_rooka(byte * ci);
void castle_info_move_rookh(byte * ci);
bool castle_info_can_castle_short(byte ci);
bool castle_info_can_castle_long(byte ci);

//pos
Position Position_init(Board board, Move last_move, byte ci_white, byte ci_black);
Position Position_init_from_cstr(const char * cstr, Move last_move, byte ci_white, byte ci_black);
Position Position_init_default(void);
CLR Position_to_move(const Position * position);
char * Position_Board_cstr(const Position * position);
void Position_apply_move(Position * pos, Move mv);

BrdInfo BrdInfo_init(const Board * board);
// bool BrdInfo_square_attacked_by(const BrdInfo * pos_info, int idx, CLR clr);
// bool BrdInfo_in_check(const BrdInfo * pos_info, CLR clr);

//dbg
void dbg_mask(u64 mask);
void dbg_Board(const Board * board);
void dbg_BrdInfo(const BrdInfo * pi);

#endif