#ifndef GUI_H
#define GUI_H

#include "common.h"

typedef struct Gui Gui;

Gui *   Gui_start(void);
int     Gui_draw(const Gui * gui);
int     Gui_stop(Gui * gui);
Move    Gui_handle_input(Gui * gui);
int     Gui_data_size(const Gui * gui);
int     Gui_Board_set_cstr(Gui * gui, const char * cstr);

#endif