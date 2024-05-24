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

char * Board_get(const Board * board, int idx)
{
    return (char *) board->squares + idx;
}

char Board_at(const Board * board, int idx)
{
    return * Board_get(board, idx);
}

char Board_at_rc(const Board * board, int row, int col)
{
    return Board_at(board, _row_col_idx(row, col));
}

void Board_set(Board * board, int idx, char piece)
{
    * Board_get(board, idx) = piece;
}

bool Board_square_is(const Board * board, int idx, char piece)
{
    return Board_at(board, idx) == piece;
}

bool Board_square_isf(const Board * board, int row, int col, bool (* f)(char))
{
    return f(Board_at_rc(board, row, col));
}

bool Board_square_empty(const Board * board, int idx)
{
    return Board_square_is(board, idx, CHESS_PIECE_NONE);
}

CLR Board_square_piece_clr(const Board * board, int idx)
{
    return piece_clr(Board_at(board, idx));
}

bool Board_square_piece_same_clr(const Board * board, int lhs, int rhs)
{
    return piece_clr(Board_at(board, lhs)) == piece_clr(Board_at(board, rhs));
}

bool Board_move_is_capture(const Board * board, Move mv)
{
    if (Board_square_empty(board, mv.from) || Board_square_empty(board, mv.to)) return false;

    return ! Board_square_piece_same_clr(board, mv.from, mv.to);
}

void Board_move(Board * board, int from, int to)
{
    Board_set(board, to, Board_at(board, from));
    Board_set(board, from, CHESS_PIECE_NONE);
}

Board Board_move_copy(const Board * board, int from, int to)
{
    Board new;

    new = Board_init_copy(board);
    Board_move(& new, from, to);

    return new;
}

void Board_move_Move(Board * board, Move mv)
{
    Board_move(board, mv.from, mv.to);
}

int Board_row_distance(int a_row, int b_row)
{
    return abs_(a_row - b_row);
}

int Board_col_distance(int a_col, int b_col)
{
    return abs_(a_col - b_col);
}

int Board_distance_row_col(int a_row, int a_col, int b_row, int b_col)
{
    int dx, dy;

    dx = Board_col_distance(a_col, b_col);
    dy = Board_row_distance(a_row, b_row);

    return max_(dx, dy);
}

int Board_distance(int from, int to)
{
    return Board_distance_row_col(_idx_row(from), _idx_col(from), _idx_row(to), _idx_col(to));
}

int Board_find_king(const Board * board, CLR clr)
{
    for (int k = 0; k < CHESS_BOARD_SIZE; k ++)
    {
        if (piece_king_clr(Board_at(board, k), clr)) return k;
    }

    return NO_IDX;
}

u64 Board_hash(const Board * board)
{
    return hash_djb((const byte *) board->squares, CHESS_BOARD_SIZE);
}