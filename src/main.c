#include "Gui.h"
//
#include "../chess/Chess.h"
//

#include <stdio.h>
#include "raylib.h"

int main(void)
{
    Gui *   gui;
    Chess * chess;
    Move    mv;

    if (! (gui = Gui_start())) return 0;
    if (! (chess = Chess_new_game())) return 0;

    Gui_Board_set_cstr(gui, Chess_get_board_cstr(chess));

    while (! WindowShouldClose())
    {
        mv = Gui_handle_input(gui);
        Gui_draw(gui);

        //
        if (Move_valid(mv))
        {
            printf("%d %d\n", mv.to, mv.from);
            Chess_dbg(chess);
        }
        //
    }
    
    Chess_del(chess);
    Gui_stop(gui);
}