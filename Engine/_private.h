#ifndef _PRIVATE_H
#define _PRIVATE_H

#include "Engine.h"
#include "../../libUI/libUI.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIDE        (8)
#define BRD_SIZE    (SIDE * SIDE)
#define KINGS_CSTR  "kK"
#define QUEENS_CSTR "qQ"
#define BISH_CSTR   "bB"
#define KNIGTS_CSTR "nN"
#define ROOKS_CSTR  "rR"
#define PAWN_CSTR   "pP"

typedef struct Brd Brd;

struct Brd
{
    char sqr[BRD_SIZE];
};

typedef enum CLR CLR;

enum CLR
{
    CLR_W,
    CLR_B,
    CLR_COUNT,
};

static inline CLR _clr_invert(CLR clr)
{
    return ! clr;
}

static inline CLR _piece_clr(char x)
{
    if (islower(x)) return CLR_W;
    if (isupper(x)) return CLR_B;

    return CLR_COUNT;
}

static inline bool _piece_king(char x)
{
    return x == KINGS_CSTR[0] || x == KINGS_CSTR[1];
}

static inline char _piece(const char * cstr, CLR clr)
{
    return cstr[clr];
}

typedef struct CstlData CstlData;

struct CstlData
{
    bool lr_moved;
    bool king_moved;
    bool rr_moved;
};

static inline bool CstlData_lc_allowed(CstlData cd)
{
    return ! cd.king_moved && ! cd.lr_moved;
}

static inline bool CstrData_rc_allowed(CstlData cd)
{
    return ! cd.king_moved && ! cd.rr_moved;
}

typedef struct Pos Pos;

struct Pos
{
    Brd         brd;
    CstlData    cstl_data[CLR_COUNT];
    CLR         move;
};

struct Game
{
    Pos pos;
    int moven;
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

static inline bool _row_col_valid(int row, int col)
{
    return (row >= 0 && row < SIDE && col >= 0 && col < SIDE);
}

void    Brd_set_cstr(Brd * brd, const char * cstr);
Brd     Brd_init_cstr(const char * cstr);
char *  Brd_get(const Brd * brd, int idx);
char *  Brd_get_rc(const Brd * brd, int row, int col);
void    Brd_set(Brd * brd, int idx, char x);
void    Brd_set_rc(Brd * brd, int row, int col, char x);
bool    Brd_is(const Brd * brd, int idx, char x);
bool    Brd_is_rc(const Brd * brd, int row, int col, char x);
bool    Brd_is_rc_checked(const Brd * brd, int row, int col, char x);
bool    Brd_attacked_rc(const Brd * brd, int row, int col, CLR clr);
void    Brd_move(Brd * brd, int from, int to);
int     Brd_find_king(const Brd * brd, CLR clr);


Pos     Pos_init(Brd brd, CstlData wcd, CstlData bcd, CLR move);
bool    Pos_init_cstr(Pos * pos, const char * cstr);
char *  Pos_get_cstr(const Pos * pos);
bool    Pos_move(const Pos * current, Pos * next, int from, int to);

void    dbg_mask(u64 mask);

#endif