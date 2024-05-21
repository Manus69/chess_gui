#include "_private.h"

void Obj_center(Obj * obj, Vector2 xy)
{
    obj->rect.x = xy.x - obj->rect.width / 2;
    obj->rect.y = xy.y - obj->rect.height / 2;
}