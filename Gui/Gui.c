#include "_private.h"

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

static const GOBJ_TYPE _gobj_tbl[] =
{
    [' '] = GOBJ_NONE,
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

static GOBJ_TYPE _ct(char x)
{
    return _gobj_tbl[(int) x];
}

void Gui_send_cstr(Gui * gui, const char * cstr)
{
    GOBJ_TYPE type;

    if (! cstr) return ;

    Gui_remove_pieces(gui);

    for (int k = 0; k < NSQUARES; k ++)
    {
        type = _ct(cstr[k]);
        if (type != GOBJ_NONE) Gui_place_piece(gui, type, _idx_row(k), _idx_col(k));
    }
}

static GuiMsg _move(Gui * gui, Vector2 xy)
{
    int_int rc_to, rc_from;

    rc_to = Box_grid_collision_xy(gui->board, xy.x, xy.y);
    if (rc_to.a == NO_IDX) return (GuiMsg) {};

    rc_from = Box_grid_collision_xy(gui->board, gui->input.click_xy.x, gui->input.click_xy.y);
    gui->selection.obj = 0;

    return (GuiMsg)
    {
        .event = GUI_EVENT_MOVE,
        .from = _row_col_idx(rc_from.a, rc_from.b),
        .to = _row_col_idx(rc_to.a, rc_to.b),
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

    return (GuiMsg) {};
}

