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

        Gui_restore(gui);
        if (Chess_try_move(chess, mv.mv))
        {
            Gui_Board_set_cstr(gui, Chess_get_board_cstr(chess));
        }
    }
}

//remove attack mask computations from brdinfo ?
//REL PATH FOR TEXTURE

int main(void)
{
    Gui *       gui;
    Chess *     chess;

    if (! (chess = Chess_new_game()))   return 0;

    //
    // Chess_init_from_Pos_cstr(chess, "rnbqkbnrpppp_ppp____________p_______P___________PPPP_PPPRNBQKBNR 12 28 000 000");
    // Chess_init_from_Pos_cstr(chess, "rnbqk__rppppbppp_____n______p_______P________N__PPPPBPPPRNBQK__R 6 21 000 000");
    Chess_init_from_Pos_cstr(chess, "r___kbnrpppqpppp__n________p__B_____P_Q___NP____PPP__PPPR___KBNR 59 38 000 000");
    //

    if (! (gui = Gui_start()))          return 0;

    Gui_Board_set_cstr(gui, Chess_get_board_cstr(chess));

    while (! WindowShouldClose())
    {
        Gui_draw(gui);
        _loop(chess, gui);
    }
    
    Chess_del(chess);
    Gui_stop(gui);
}