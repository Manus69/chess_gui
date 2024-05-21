#include "Gui.h"
//
#include "../chess/Chess.h"
//

#include <stdio.h>
#include "raylib.h"

int main(void)
{
    Gui *   gui;
    Move    mv;

    if (! (gui = Gui_start())) return 0;
    
    Gui_Board_set_cstr(gui, Chess_default_pos_cstr());

    while (! WindowShouldClose())
    {
        mv = Gui_handle_input(gui);
        Gui_draw(gui);

        //
        if (Move_valid(mv)) printf("%d %d\n", mv.to, mv.from);
        //
    }
    
    Gui_stop(gui);
}