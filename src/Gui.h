#ifndef GUI_H
#define GUI_H

#include "common.h"

typedef struct Gui      Gui;
typedef struct GuiMove  GuiMove;

struct GuiMove
{
    Move mv;
    bool attempted;
};

Gui *       Gui_start(void);
int         Gui_draw(const Gui * gui);
int         Gui_stop(Gui * gui);
GuiMove     Gui_handle_input(Gui * gui);
int         Gui_data_size(const Gui * gui);
int         Gui_Board_set_cstr(Gui * gui, const char * cstr);
void        Gui_reset(Gui * gui);
void        Gui_restore(Gui * gui);

#endif