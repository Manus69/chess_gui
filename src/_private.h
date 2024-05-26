#ifndef _PRIVATE_H
#define _PRIVATE_H

#include    "Gui.h"

#define     CHESS_PATH          "../chess/Chess.h"
#include    CHESS_PATH

#include    <stdlib.h>
#include    <stdio.h>
#include    "raylib.h"

#define     GUI_BOARD_SIDE      COMMON_BOARD_SIDE
#define     GUI_BOARD_SIZE      COMMON_BOARD_SIZE
#define     GUI_N_PIECES        (GUI_BOARD_SIZE / 2)

typedef struct TxLayout     TxLayout;
typedef struct Tx           Tx;
typedef struct Obj          Obj;
typedef struct GuiBoard     GuiBoard;
typedef struct Selection    Selection;
typedef struct Layout       Layout;
typedef struct Input        Input;
typedef enum   GUI_TYPE     GUI_TYPE;

enum GUI_TYPE
{
    GUI_NONE,
    GUI_BOARD,
    GUI_WK,
    GUI_BK,
    GUI_WQ,
    GUI_BQ,
    GUI_WB,
    GUI_BB,
    GUI_WN,
    GUI_BN,
    GUI_WR,
    GUI_BR,
    GUI_WP,
    GUI_BP,
    GUI_BUTTON,
    GUI_ELEM_MAX,
};

struct TxLayout
{
    Rectangle   layout[GUI_ELEM_MAX];
};

struct Tx
{
    TxLayout    tx_layout;
    Texture2D   texture;
};

struct Obj
{
    GUI_TYPE    type;
    Rectangle   rect;
};

struct GuiBoard
{
    GUI_TYPE    type;
    Rectangle   rect;
    Obj         squares[GUI_BOARD_SIZE];
};

struct Selection
{
    Obj *   obj;
    Obj     initial;
    int     idx;
};

struct Layout
{
    Rectangle   window;
    GuiBoard    board;
    Selection   selection;
};

struct Input
{
    Vector2 mouse;
    bool    click;
    bool    mose_down;
};

struct Gui
{
    Tx      tx;
    Layout  layout;
    Input   input;
};

static inline GUI_TYPE _chess_piece_to_gui_type(char x)
{
    if (x == CHESS_PIECE_NONE) return GUI_NONE;
    if (x == CHESS_PIECE_WP) return GUI_WP;
    if (x == CHESS_PIECE_BP) return GUI_BP;
    if (x == CHESS_PIECE_WK) return GUI_WK;
    if (x == CHESS_PIECE_BK) return GUI_BK;
    if (x == CHESS_PIECE_WQ) return GUI_WQ;
    if (x == CHESS_PIECE_BQ) return GUI_BQ;
    if (x == CHESS_PIECE_WB) return GUI_WB;
    if (x == CHESS_PIECE_BB) return GUI_BB;
    if (x == CHESS_PIECE_WN) return GUI_WN;
    if (x == CHESS_PIECE_BN) return GUI_BN;
    if (x == CHESS_PIECE_WR) return GUI_WR;
    if (x == CHESS_PIECE_BR) return GUI_BR;

    return GUI_NONE;
}

void Obj_center(Obj * obj, Vector2 xy);

TxLayout    TxLayout_default(void);

GuiBoard   GuiBoard_init(float x, float y, float size);
Obj     GuiBoard_as_Obj(GuiBoard board);
Obj * GuiBoard_get(const GuiBoard * board, int idx);
void GuiBoard_place(GuiBoard * board, int idx, Obj obj);
void GuiBoard_place_piece(GuiBoard * board, int idx, GUI_TYPE type);
void GuiBoard_place_from_cstr(GuiBoard * board, const char * cstr);
float GuiBoard_square_size(const GuiBoard * board);

Layout Layout_default(int ww, int wh);
bool Layout_Board_hovered(const Layout * layout, Vector2 xy);
int Layout_square_hovered(const Layout * layout, Vector2 xy);
void Layout_select(Layout * layout, Obj * obj);
void Layout_select_square(Layout * layout, int idx);
void Layout_restore_selection(Layout * layout);
void Layout_deselect(Layout * layout);
bool Layout_has_selection(const Layout * layout);
Obj * Layout_get_selection_obj(const Layout * layout);
void Layout_dbg(const Layout * layout);
void Layout_selection_dbg(const Layout * layout);

Texture2D Gui_texture(const Gui * gui);
void Gui_process_input(Gui * gui);

#endif