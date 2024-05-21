#include "_private.h"

static void _init_squares(Board * board)
{
    float   square_size;
    int     idx;

    square_size = board->rect.width / GUI_BOARD_SIDE;

    for (int row = 0; row < GUI_BOARD_SIDE; row ++)
    {
        for (int col = 0; col < GUI_BOARD_SIDE; col ++)
        {
            idx = _row_col_idx(row, col);
            board->squares[idx] = (Obj)
            {
                .rect = (Rectangle)
                {
                    .x = board->rect.x + square_size * col,
                    .y = board->rect.y + square_size * row,
                    .width = square_size,
                    .height = square_size,
                },
            };
        }
    }
}

Board Board_init(float x, float y, float size)
{
    Board board;

    board.type = GUI_BOARD;
    board.rect = (Rectangle)
    {
        .x = x,
        .y = y,
        .width = size,
        .height = size,
    };

    _init_squares(& board);

    return board;
}

Obj Board_as_Obj(Board board)
{
    return (Obj)
    {
        .type = board.type,
        .rect = board.rect,
    };
}

float Board_square_size(const Board * board)
{
    return board->squares->rect.width;
}

Obj * Board_get(const Board * board, int idx)
{
    return (Obj *) board->squares + idx;
}

void Board_place(Board * board, int idx, Obj obj)
{
    * Board_get(board, idx) = obj;
}

void Board_place_piece(Board * board, int idx, GUI_TYPE type)
{
    Board_get(board, idx)->type = type;
}

void Board_place_from_cstr(Board * board, const char * cstr)
{
    for (int k = 0; k < GUI_BOARD_SIZE; k ++)
    {
        Board_place_piece(board, k, _chess_piece_to_gui_type(cstr[k]));
    }
}
