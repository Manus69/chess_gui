#include "_private.h"

Board Board_init_empty(void)
{
    Board board = {};

    return board;
}

Board Board_init_cstr(const char * cstr)
{
    Board board;

    memcpy(board.squares, cstr, CHESS_BOARD_SIZE);

    return board;
}

Board Board_init_copy(const Board * board)
{
    return Board_init_cstr(board->squares);
}

char * Board_get(Board * board, int idx)
{
    return board->squares + idx;
}

char Board_at(const Board * board, int idx)
{
    return * Board_get(board, idx);
}

void Board_set(Board * board, int idx, char piece)
{
    * Board_get(board, idx) = piece;
}

bool Board_is_square(const Board * board, int idx, char piece)
{
    return Board_at(board, idx) == piece;
}

void Board_move(Board * board, int from, int to)
{
    Board_set(board, to, Board_at(board, from));
    Board_set(board, from, CHESS_PIECE_NONE);
}

u64 Board_hash(const Board * board)
{
    return hash_djb(board->squares, CHESS_BOARD_SIZE);
}