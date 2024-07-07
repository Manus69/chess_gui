#ifndef GUI_H
#define GUI_H

// typedef enum GUI_EVENT GUI_EVENT;

typedef enum GUI_EVENT : char
{
    GUI_EVENT_NONE,
    GUI_EVENT_MOVE,
    GUI_EVENT_RESET,
    GUI_EVENT_COUNT,
}   GUI_EVENT;

typedef struct GuiMsg GuiMsg;

struct GuiMsg
{
    GUI_EVENT   event;
    char        from;
    char        to;
};

typedef struct Gui Gui;

Gui *   Gui_new(void);
void    Gui_del(Gui * gui);
GuiMsg  Gui_get_Msg(Gui * gui);
void    Gui_recieve_cstr(Gui * gui, const char * cstr);
void    Gui_draw(const Gui * gui);

#endif