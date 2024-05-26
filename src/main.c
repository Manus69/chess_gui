#include "Gui.h"
#include "../chess/Chess.h"

#include <stdio.h>
#include "raylib.h"

static void _loop(Chess * chess, Gui * gui)
{
    GuiMove mv;

    mv = Gui_handle_input(gui);
    if (mv.attempted)
    {
        //
        Chess_dbg(chess);
        //

        if (Chess_try_move(chess, mv.mv))
        {
            Gui_reset(gui);
            Gui_Board_set_cstr(gui, Chess_get_board_cstr(chess));
        }
        else
        {
            Gui_restore(gui);
        }
    }
}

//remove attack mask computations from brdinfo ?
//REL PATH FOR TEXTURE

int main(void)
{
    Gui *       gui;
    Chess *     chess;

    if (! (gui = Gui_start()))          return 0;
    if (! (chess = Chess_new_game()))   return 0;

    Gui_Board_set_cstr(gui, Chess_get_board_cstr(chess));

    while (! WindowShouldClose())
    {
        Gui_draw(gui);
        _loop(chess, gui);
    }
    
    Chess_del(chess);
    Gui_stop(gui);
}