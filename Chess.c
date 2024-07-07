#include "Gui/Gui.h"
#include "Engine/Engine.h"
#include "raylib.h"

#include <stdio.h>

const char * pcstr = "RNBQK__RPPPP_PPP_____N____B_P_____b_p________n__pppp_ppprnbqk__r 000 000 5 26";


//add en passant
//flip board?

int main()
{
    Game *  game;
    Gui *   gui;
    GuiMsg  msg;

    if (! (gui = Gui_new()))                    return 1;
    if (! (game = Game_new_from_cstr(pcstr)))   return 1;

    Gui_recieve_cstr(gui, Game_Brd_cstr(game));

    while (! WindowShouldClose())
    {
        msg = Gui_get_Msg(gui);

        if (msg.event == GUI_EVENT_RESET)
        {
            Game_reset(game);
            Gui_recieve_cstr(gui, Game_Brd_cstr(game));
        }
        else if (msg.event)
        {
            printf("%d %d\n", msg.from, msg.to);
            Game_try_move(game, msg.from, msg.to);
            Gui_recieve_cstr(gui, Game_Brd_cstr(game));
        }
        
        Gui_draw(gui);
    }
    
    Game_del(game);
    Gui_del(gui);
    
    return 0;
}
