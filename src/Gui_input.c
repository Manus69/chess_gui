#include "_private.h"

void Gui_process_input(Gui * gui)
{
    gui->input.mouse = GetMousePosition();
    gui->input.click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    gui->input.mose_down = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
}

static void _deselect(Gui * gui)
{
    Layout_restore_selection(& gui->layout);
}

static void _move_piece(Gui * gui)
{
    Obj_center(Layout_get_selection_obj(& gui->layout), gui->input.mouse);
}

static void _select_piece(Gui * gui)
{
    int idx;

    idx = Layout_square_hovered(& gui->layout, gui->input.mouse);
    if (idx != NO_IDX) Layout_select_square(& gui->layout, idx);

    _move_piece(gui);
}

static Move _drop_piece(Gui * gui)
{
    int to, from;

    to = Layout_square_hovered(& gui->layout, gui->input.mouse);
    from = gui->layout.selection.idx;

    // if (to == NO_IDX) _deselect(gui);
    _deselect(gui);

    return Move_init(from, to);
}

Move Gui_handle_input(Gui * gui)
{
    Gui_process_input(gui);

    if (gui->input.click)
    {
        _select_piece(gui);
    }
    else if (gui->input.mose_down && Layout_has_selection(& gui->layout))
    {
        _move_piece(gui);
    }
    else if (! gui->input.mose_down && Layout_has_selection(& gui->layout))
    {
        return _drop_piece(gui);
    }

    return Move_init_no_move();
}