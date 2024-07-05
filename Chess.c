#include "Gui/Gui.h"
#include "Engine/Engine.h"
#include "raylib.h"

#include <stdio.h>

#define TEST_CSTR \
"________" \
"________" \
"_K_K_K__" \
"________" \
"________" \
"________" \
"________" \
"_kk_pP__"

int main()
{
    Game *  game;
    Gui *   gui;
    GuiMsg  msg;

    if (! (gui = Gui_new()))    return 1;
    if (! (game = Game_new()))  return 1;

    Gui_send_cstr(gui, Game_get_cstr(game));

    while (! WindowShouldClose())
    {
        msg = Gui_get_Msg(gui);

        if (msg.event == GUI_EVENT_RESET)
        {
            Game_reset(game);
            Gui_send_cstr(gui, Game_get_cstr(game));
        }
        else if (msg.event)
        {
            printf("%d %d\n", msg.from, msg.to);
            Game_try_move(game, msg.from, msg.to);
        }
        
        Gui_draw(gui);
    }
    
    Game_del(game);
    Gui_del(gui);
    
    return 0;
}
