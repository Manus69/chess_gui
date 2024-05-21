#include "_private.h"

#define BOARD_SIZE 800
#define PIECE_SIZE 100

static Rectangle _rect(int x, int y, int size)
{
    return (Rectangle)
    {
        .x = x,
        .y = y,
        .width = size,
        .height = size,
    };
}

TxLayout TxLayout_default(void)
{
    TxLayout layout = {};

    layout.layout[GUI_BOARD] = _rect(0, 0, BOARD_SIZE);
    layout.layout[GUI_WK] = _rect(0, BOARD_SIZE, PIECE_SIZE);
    layout.layout[GUI_WQ] = _rect(100, BOARD_SIZE, PIECE_SIZE);
    layout.layout[GUI_WB] = _rect(200, BOARD_SIZE, PIECE_SIZE);
    layout.layout[GUI_WN] = _rect(300, BOARD_SIZE, PIECE_SIZE);
    layout.layout[GUI_WR] = _rect(400, BOARD_SIZE, PIECE_SIZE);
    layout.layout[GUI_WP] = _rect(500, BOARD_SIZE, PIECE_SIZE);
    layout.layout[GUI_BK] = _rect(0, 900, PIECE_SIZE);
    layout.layout[GUI_BQ] = _rect(100, 900, PIECE_SIZE);
    layout.layout[GUI_BB] = _rect(200, 900, PIECE_SIZE);
    layout.layout[GUI_BN] = _rect(300, 900, PIECE_SIZE);
    layout.layout[GUI_BR] = _rect(400, 900, PIECE_SIZE);
    layout.layout[GUI_BP] = _rect(500, 900, PIECE_SIZE);

    return layout;
}