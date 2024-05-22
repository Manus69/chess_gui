#include "_private.h"

typedef enum PIECE_VAL PIECE_VAL;

enum PIECE_VAL
{
    PIECE_VAL_NONE = 0,
    PIECE_VAL_KING = 0,
    PIECE_VAL_PAWN = 1,
    PIECE_VAL_KNIGHT = 3,
    PIECE_VAL_BISHOP = 3,
    PIECE_VAL_ROOK = 5,
    PIECE_VAL_QUEEN = 9,
};

CLR piece_clr(char p)
{
    if (char_is_upper(p)) return CLR_WHITE;
    if (char_is_lower(p)) return CLR_BALCK;

    return CLR_NONE;
}

bool piece_none(char p)
{
    return p == CHESS_PIECE_NONE;
}

bool piece_king(char p)
{
    return p == CHESS_PIECE_WK || p == CHESS_PIECE_BK;
}

bool piece_queen(char p)
{
    return p == CHESS_PIECE_WQ || p == CHESS_PIECE_BQ;
}

bool piece_bishop(char p)
{
    return p == CHESS_PIECE_WB || p == CHESS_PIECE_BB;
}

bool piece_knight(char p)
{
    return p == CHESS_PIECE_WN || p == CHESS_PIECE_BN;
}

bool piece_rook(char p)
{
    return p == CHESS_PIECE_WR || p == CHESS_PIECE_BR;
}

bool piece_pawn(char p)
{
    return p == CHESS_PIECE_WP || p == CHESS_PIECE_BP;
}

char piece_value(char p)
{
    if (piece_none(p)) return PIECE_VAL_NONE;
    if (piece_king(p)) return PIECE_VAL_KING;
    if (piece_pawn(p)) return PIECE_VAL_PAWN;
    if (piece_knight(p)) return PIECE_VAL_KNIGHT;
    if (piece_bishop(p)) return PIECE_VAL_BISHOP;
    if (piece_rook(p)) return PIECE_VAL_ROOK;
    if (piece_queen(p)) return PIECE_VAL_QUEEN;

    return PIECE_VAL_NONE;
}