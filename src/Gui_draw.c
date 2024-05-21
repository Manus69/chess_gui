#include "_private.h"

#define V_DFLT (Vector2) {}

void _draw_obj(const Obj * obj, const Gui * gui)
{
    if (obj->type != GUI_NONE)
    {
        DrawTexturePro(Gui_texture(gui), gui->tx.tx_layout.layout[obj->type], obj->rect, V_DFLT, 0, RAYWHITE);
    }
}

void _draw_board(const Gui * gui)
{
    _draw_obj((Obj *) & gui->layout.board, gui);
    
    for (int k = 0; k < GUI_BOARD_SIZE; k ++)
    {
        _draw_obj(Board_get(& gui->layout.board, k), gui);
    }
}

void _draw_selection(const Gui * gui)
{
    if (Layout_has_selection(& gui->layout)) _draw_obj(gui->layout.selection.obj, gui);
}

int Gui_draw(const Gui * gui)
{
    BeginDrawing();
    ClearBackground(DARKGRAY);

    _draw_board(gui);
    _draw_selection(gui);

    EndDrawing();

    return OK;
}