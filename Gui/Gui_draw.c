#include "_private.h"
#include "TxAtlas.h"

#include <stdio.h>

#define BUFF_SIZE (64)
static void _draw_timer(const GuiObj * obj)
{
    char    buff[BUFF_SIZE] = {};
    time_t  ctime;

    ctime = obj->time - time(NULL);
    snprintf(buff, BUFF_SIZE, "%ld", ctime);

    DrawText(buff, obj->rect.x, obj->rect.y, obj->rect.h, BLACK);
}

static void _draw(void * _obj)
{
    GuiObj * obj;

    obj = _obj;
    if (obj->type == GOBJ_TMR) return _draw_timer(obj);

    DrawTexturePro(obj->gui->tx, _tx_atlas[obj->type], $(Rectangle) & obj->rect, (Vector2){}, 0, RAYWHITE);
}

void Gui_draw(const Gui * gui)
{
    BeginDrawing();
    ClearBackground(GRAY);
    UI_map(& gui->ui, _draw);
    EndDrawing();
}