#include "_private.h"

bool Layout_Board_hovered(const Layout * layout, Vector2 xy)
{
    return CheckCollisionPointRec(xy, layout->board.rect);
}

int Layout_square_hovered(const Layout * layout, Vector2 xy)
{
    int row, col;

    if (Layout_Board_hovered(layout, xy))
    {
        row = (xy.y - layout->board.rect.y) / GuiBoard_square_size(& layout->board);
        col = (xy.x - layout->board.rect.x) / GuiBoard_square_size(& layout->board);

        return _row_col_idx(row, col);
    }

    return NO_IDX;
}

Obj * Layout_get_selection_obj(const Layout * layout)
{
    return layout->selection.obj;
}

void Layout_select(Layout * layout, Obj * obj)
{
    layout->selection.obj = obj;
    layout->selection.initial = * obj;
}

void Layout_select_square(Layout * layout, int idx)
{
    Layout_select(layout, GuiBoard_get(& layout->board, idx));
    layout->selection.idx = idx;
}

void Layout_deselect(Layout * layout)
{
    layout->selection.obj = NULL;
}

void Layout_restore_selection(Layout * layout)
{
    if (Layout_has_selection(layout))
    {
        * layout->selection.obj = layout->selection.initial;
        Layout_deselect(layout);
    }
}

bool Layout_has_selection(const Layout * layout)
{
    return layout->selection.obj;
}

void Layout_dbg(const Layout * layout)
{
    Obj * obj;

    for (int row = 0; row < GUI_BOARD_SIDE; row ++)
    {
        for (int col = 0; col < GUI_BOARD_SIDE; col ++)
        {
            obj = GuiBoard_get(& layout->board, _row_col_idx(row, col));
            printf("(%.1f %.1f)", obj->rect.x, obj->rect.y);
        }
        nl_;
    }
    nl_;
}

void Layout_selection_dbg(const Layout * layout)
{
    if (Layout_has_selection(layout))
    {
        printf("Selection: \n");
        printf("(%.1f %.1f)", layout->selection.obj->rect.x, layout->selection.obj->rect.y);
        printf("(%.1f %.1f)", layout->selection.initial.rect.x, layout->selection.initial.rect.y);
        nl_;
    }
}