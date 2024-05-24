#include "_private.h"

static void _init_squares(GuiBoard * board)
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

GuiBoard GuiBoard_init(float x, float y, float size)
{
    GuiBoard board;

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

Obj GuiBoard_as_Obj(GuiBoard board)
{
    return (Obj)
    {
        .type = board.type,
        .rect = board.rect,
    };
}

float GuiBoard_square_size(const GuiBoard * board)
{
    return board->squares->rect.width;
}

Obj * GuiBoard_get(const GuiBoard * board, int idx)
{
    return (Obj *) board->squares + idx;
}

void GuiBoard_place(GuiBoard * board, int idx, Obj obj)
{
    * GuiBoard_get(board, idx) = obj;
}

void GuiBoard_place_piece(GuiBoard * board, int idx, GUI_TYPE type)
{
    GuiBoard_get(board, idx)->type = type;
}

void GuiBoard_place_from_cstr(GuiBoard * board, const char * cstr)
{
    for (int k = 0; k < GUI_BOARD_SIZE; k ++)
    {
        GuiBoard_place_piece(board, k, _chess_piece_to_gui_type(cstr[k]));
    }
}
