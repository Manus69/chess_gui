#ifndef _PRIVATE_H
#define _PRIVATE_H

#include "Gui.h"
#include "raylib.h"
#include "../../libUI/libUI.h"

#include <assert.h>
#include <time.h>

#define SIDE        (8)
#define NSQUARES    (SIDE * SIDE)

typedef enum GOBJ_TYPE GOBJ_TYPE;

enum GOBJ_TYPE
{
    GOBJ_NONE,
    GOBJ_BRD,
    GOBJ_WK,
    GOBJ_BK,
    GOBJ_WQ,
    GOBJ_BQ,
    GOBJ_WB,
    GOBJ_BB,
    GOBJ_WN,
    GOBJ_BN,
    GOBJ_WR,
    GOBJ_BR,
    GOBJ_WP,
    GOBJ_BP,
    GOBJ_TMR,
    GOBJ_COUNT,
};

typedef struct GuiObj GuiObj;

struct GuiObj
{
    Gui *       gui;
    GOBJ_TYPE   type;
    Rect        rect;
    time_t      time;
};

static inline bool GuiObj_collision_xy(const void * go, float x, float y)
{
    return Rect_collision_xy(& ((GuiObj *) go)->rect, x, y);
}

typedef struct Input Input;

struct Input
{
    Vector2     click_xy;
    bool        lmb_down;
};

typedef struct Selection Selection;

struct Selection
{
    GuiObj *    obj; 
    Rect        initial;
};

struct Gui
{
    char        msg_buff[NSQUARES];
    UI          ui;
    Box *       board;
    Texture2D   tx;
    Selection   selection;
    Input       input;
    bool        flip;
};

static inline int _idx_row(int idx)
{
    return idx / SIDE;
}

static inline int _idx_col(int idx)
{
    return idx % SIDE;
}

static inline int _row_col_idx(int row, int col)
{
    return row * SIDE + col;
}

static inline int Gui_map_idx(const Gui * gui, int idx)
{
    return idx * ! gui->flip + (NSQUARES - idx - 1) * gui->flip;
}

#endif