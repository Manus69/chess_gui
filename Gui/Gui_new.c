#include "_private.h"

#include <stdlib.h>

#define TX_PATH     ("./assets/texture.png")
#define CAPACITY    (1 << 7)
#define PAD         (10)

static const Rect _board_rect = (Rect)
{
    .x = PAD,
    .y = PAD,
    .w = 800,
    .h = 800,
};

static const Rect _panel_rect = (Rect)
{
    .x = _board_rect.w + 2 * PAD,
    .y = PAD,
    .w = 200,
    .h = 800,
};

static void _add_board(Gui * gui)
{
    GuiObj obj;

    UI_add_Box(& gui->ui, _board_rect, 1, 1);

    obj = (GuiObj)
    {
        .gui = gui,
        .rect = _board_rect,
        .type = GOBJ_BRD,
    };

    UI_add_item_Box(& gui->ui, UI_get_top_Box(& gui->ui), & obj);

    UI_add_Box(& gui->ui, _board_rect, SIDE, SIDE);
    gui->board = UI_get_top_Box(& gui->ui);
}

static void _add_tmr(Gui * gui)
{
    GuiObj  obj;
    Rect    rect;

    UI_add_Box(& gui->ui, _panel_rect, 8, 1);

    rect = Box_get_grid_Rect(UI_get_top_Box(& gui->ui), 0, 0);

    obj = (GuiObj)
    {
        .gui = gui,
        .rect = rect,
        .type = GOBJ_TMR,
        .time = time(NULL) + 1000,
    };

    UI_add_item_Box(& gui->ui, UI_get_top_Box(& gui->ui), & obj);
}

Gui * Gui_new(void)
{
    Gui * gui;

    if (! (gui = calloc(1, sizeof(* gui))))             return NULL;
    if (! UI_new(& gui->ui, sizeof(GuiObj), CAPACITY))  return NULL;

    _add_board(gui);
    _add_tmr(gui);

    InitWindow(gui->ui.bound.w + PAD, gui->ui.bound.h + PAD, "");
    SetTargetFPS(60);

    gui->tx = LoadTexture(TX_PATH);
    assert(gui->tx.id);

    return gui;
}

void Gui_del(Gui * gui)
{
    UnloadTexture(gui->tx);
    CloseWindow();

    UI_del(& gui->ui);
    free(gui);
}