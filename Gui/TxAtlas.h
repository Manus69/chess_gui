#ifndef TXATLAS_H
#define TXATLAS_H

#include "_private.h"

#define SIZE (100)
#define WROW (800)
#define BROW (900)

static const Rectangle _tx_atlas[] =
{
    [GOBJ_BRD] =    (Rectangle) {0, 0, 800, 800},
    [GOBJ_WK] =     (Rectangle) {0, WROW, SIZE, SIZE},
    [GOBJ_BK] =     (Rectangle) {0, BROW, SIZE, SIZE},
    [GOBJ_WQ] =     (Rectangle) {100, WROW, SIZE, SIZE},
    [GOBJ_BQ] =     (Rectangle) {100, BROW, SIZE, SIZE},
    [GOBJ_WB] =     (Rectangle) {200, WROW, SIZE, SIZE},
    [GOBJ_BB] =     (Rectangle) {200, BROW, SIZE, SIZE},
    [GOBJ_WN] =     (Rectangle) {300, WROW, SIZE, SIZE},
    [GOBJ_BN] =     (Rectangle) {300, BROW, SIZE, SIZE},
    [GOBJ_WR] =     (Rectangle) {400, WROW, SIZE, SIZE},
    [GOBJ_BR] =     (Rectangle) {400, BROW, SIZE, SIZE},
    [GOBJ_WP] =     (Rectangle) {500, WROW, SIZE, SIZE},
    [GOBJ_BP] =     (Rectangle) {500, BROW, SIZE, SIZE},
};

#endif