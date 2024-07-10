#ifndef _PRIVATE_H
#define _PRIVATE_H

#include "Engine.h"
#include "../../libUI/libUI.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIDE        (8)
#define BRD_SIZE    (SIDE * SIDE)
#define KING_CSTR   "kK"
#define QUEEN_CSTR  "qQ"
#define BISH_CSTR   "bB"
#define KNIGHT_CSTR "nN"
#define ROOK_CSTR   "rR"
#define PAWN_CSTR   "pP"

$pair_gen(char, char)

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
    return x == KING_CSTR[0] || x == KING_CSTR[1];
}

static inline bool _piece_knight(char x)
{
    return x == KNIGHT_CSTR[0] || x == KNIGHT_CSTR[1];
}

static inline bool _piece_bish(char x)
{
    return x == BISH_CSTR[0] || x == BISH_CSTR[1];
}

static inline bool _piece_rook(char x)
{
    return x == ROOK_CSTR[0] || x == ROOK_CSTR[1];
}

static inline bool _piece_queen(char x)
{
    return x == QUEEN_CSTR[0] || x == QUEEN_CSTR[1];
}

static inline bool _piece_pawn(char x)
{
    return x == PAWN_CSTR[0] || x == PAWN_CSTR[1];
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
    char        king_idx[CLR_COUNT];
    int_int     last_move;
    CLR         move_clr;
};

typedef struct Eng Eng;

struct Eng
{
    Vec move_vec;
};

struct Game
{
    Eng *    eng;
    Pos      pos_initial;
    Pos      pos;
    int      moven;
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
    return row >= 0 && row < SIDE && col >= 0 && col < SIDE;
}

static inline bool _idx_valid(int idx)
{
    return idx >= 0 && idx < BRD_SIZE;
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
bool    Brd_is_empty_rc(const Brd * brd, int row, int col);
bool    Brd_is_CLR(const Brd * brd, int idx, CLR clr);
bool    Brd_attacked_rc(const Brd * brd, int row, int col, CLR clr);
void    Brd_move(Brd * brd, int from, int to);
int     Brd_find_king(const Brd * brd, CLR clr);

Pos     Pos_init(Brd brd, CstlData wcd, CstlData bcd, int_int last_move, CLR move_clr);
Pos     Pos_init_default(Brd brd);
CLR     Pos_turn(const Pos * pos);
bool    Pos_from_cstr(Pos * pos, const char * cstr);
char *  Pos_Brd_cstr(const Pos * pos);
u64     Pos_compute_mmask(const Pos * pos, int idx);
bool    Pos_try_move(const Pos * current, Pos * next, int from, int to);
void    Pos_apply_move(Pos * pos, int from, int to);
bool    Pos_in_check(const Pos * pos, CLR clr);
bool    Pos_any_moves(const Pos * pos, CLR clr);

bool    Eng_init(Eng * eng);
Eng *   Eng_new(void);
void    Eng_del(Eng * eng);
Vec *   Eng_get_moves_square(Eng * engine, const Pos * pos, int idx);
Vec *   Eng_get_moves_CLR(Eng * engine, const Pos * pos, CLR clr);
Vec *   Eng_get_moves(Eng * eng, const Pos * pos);
void    Eng_movevec_reset(Eng * eng);
i32     Eng_movevec_len(const Eng * eng);


void    dbg_mask(u64 mask);
void    dbg_msg(const char * msg, const char * file, int line);
void    dbg_Pos(const Pos * pos);
void    dbg_move(char_char mv);
void    dbg_movef(void * mv);

#endif