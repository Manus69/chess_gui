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
        row = (xy.y - layout->board.rect.y) / Board_square_size(& layout->board);
        col = (xy.x - layout->board.rect.x) / Board_square_size(& layout->board);

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
    Layout_select(layout, Board_get(& layout->board, idx));
    layout->selection.idx = idx;
}

void Layout_deselect(Layout * layout)
{
    layout->selection.obj = NULL;
}

void Layout_restore_selection(Layout * layout)
{
    * layout->selection.obj = layout->selection.initial;
    Layout_deselect(layout);
}

bool Layout_has_selection(const Layout * layout)
{
    return layout->selection.obj;
}