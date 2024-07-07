#include "_private.h"

#include <string.h>

void Gui_place_piece(Gui * gui, GOBJ_TYPE type, int row, int col)
{
    GuiObj obj;

    obj = (GuiObj)
    {
        .gui = gui,
        .rect = Box_get_grid_Rect(gui->board, row, col),
        .type = type,
    };

    UI_add_item_Box(& gui->ui, gui->board, & obj);
}

void Gui_remove_pieces(Gui * gui)
{
    UI_remove_items_Box(& gui->ui, gui->board);
}

static GOBJ_TYPE _ct(char x)
{
    static const GOBJ_TYPE _gobj_tbl[] =
    {
        ['_'] = GOBJ_NONE,
        ['k'] = GOBJ_WK,
        ['q'] = GOBJ_WQ,
        ['b'] = GOBJ_WB,
        ['n'] = GOBJ_WN,
        ['r'] = GOBJ_WR,
        ['p'] = GOBJ_WP,
        ['K'] = GOBJ_BK,
        ['Q'] = GOBJ_BQ,
        ['B'] = GOBJ_BB,
        ['N'] = GOBJ_BN,
        ['R'] = GOBJ_BR,
        ['P'] = GOBJ_BP,
    };

    return _gobj_tbl[(int) x];
}

void Gui_parse_buffer(Gui * gui)
{
    GOBJ_TYPE   type;
    int         idx;

    Gui_remove_pieces(gui);

    for (int k = 0; k < NSQUARES; k ++)
    {
        type = _ct(gui->msg_buff[k]);
        if (type != GOBJ_NONE) 
        {
            idx = Gui_map_idx(gui, k);

            // Gui_place_piece(gui, type, _idx_row(k), _idx_col(k));
            Gui_place_piece(gui, type, _idx_row(idx), _idx_col(idx));
        }
    }
}

void Gui_recieve_cstr(Gui * gui, const char * cstr)
{
    if (! cstr) return ;

    memcpy(gui->msg_buff, cstr, NSQUARES);
    
    Gui_parse_buffer(gui);
}

void Gui_flip(Gui * gui)
{
    gui->flip = ! gui->flip;
    Gui_parse_buffer(gui);
}

static GuiMsg _move(Gui * gui, Vector2 xy)
{
    int_int rc_to, rc_from;
    int     from, to;

    rc_to = Box_grid_collision_xy(gui->board, xy.x, xy.y);
    
    if (rc_to.a == NO_IDX)
    {
        gui->selection.obj->rect = gui->selection.initial;
        gui->selection.obj = NULL;

        return (GuiMsg) {};
    }

    gui->selection.obj = NULL;
    rc_from = Box_grid_collision_xy(gui->board, gui->input.click_xy.x, gui->input.click_xy.y);

    from = Gui_map_idx(gui, _row_col_idx(rc_from.a, rc_from.b));
    to = Gui_map_idx(gui, _row_col_idx(rc_to.a, rc_to.b));

    return (GuiMsg)
    {
        .event = GUI_EVENT_MOVE,
        .from = from,
        .to = to,
    };
}

GuiMsg Gui_get_Msg(Gui * gui)
{
    Vector2 xy;
    int     id;

    xy = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        gui->input.click_xy = xy;
        gui->input.lmb_down = true;

        id = UI_item_collision_xy(& gui->ui, xy.x, xy.y, GuiObj_collision_xy);

        if (id >= 0 && Box_contains(gui->board, id))
        {
            gui->selection.obj = UI_get_item(& gui->ui, id);
            gui->selection.initial = gui->selection.obj->rect;
        }

        return (GuiMsg) {};
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && gui->selection.obj)
    {
        gui->input.lmb_down = false;
        
        return _move(gui, xy);
    }

    if (gui->input.lmb_down && gui->selection.obj)
    {
        Rect_center_at(& gui->selection.obj->rect, xy.x, xy.y);

        return (GuiMsg) {};
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        return (GuiMsg) {.event = GUI_EVENT_RESET};
    }

    if (IsKeyPressed(KEY_F))
    {
        Gui_flip(gui);
    }

    return (GuiMsg) {};
}

