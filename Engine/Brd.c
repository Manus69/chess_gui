#include "_private.h"

void Brd_set_cstr(Brd * brd, const char * cstr)
{
    memcpy(brd->sqr, cstr, BRD_SIZE);
}

Brd Brd_init_cstr(const char * cstr)
{
    Brd brd;

    Brd_set_cstr(& brd, cstr);

    return brd;
}

char * Brd_get(const Brd * brd, int idx)
{
    return (char *) brd->sqr + idx;
}

char * Brd_get_rc(const Brd * brd, int row, int col)
{
    return Brd_get(brd, _row_col_idx(row, col));
}

void Brd_set(Brd * brd, int idx, char x)
{
    * Brd_get(brd, idx) = x;
}

void Brd_set_rc(Brd * brd, int row, int col, char x)
{
    Brd_set(brd, _row_col_idx(row, col), x);
}

void Brd_move(Brd * brd, int from, int to)
{
    char x;

    x = * Brd_get(brd, from);
    Brd_set(brd, to, x);
    Brd_set(brd, from, '_');
}

bool Brd_is_rc(const Brd * brd, int row, int col, char x)
{
    return * Brd_get_rc(brd, row, col) == x;
}

bool Brd_is_empty_rc(const Brd * brd, int row, int col)
{
    return Brd_is_rc(brd, row, col, '_');
}

bool Brd_is(const Brd * brd, int idx, char x)
{
    return * Brd_get(brd, idx) == x;
}

bool Brd_is_rc_checked(const Brd * brd, int row, int col, char x)
{
    if (_row_col_valid(row, col))
    {
        return Brd_is_rc(brd, row, col, x);
    }

    return false;
}

bool Brd_is_CLR(const Brd * brd, int idx, CLR clr)
{
    return _piece_clr(* Brd_get(brd, idx)) == clr;
}

static bool _attacked_wp(const Brd * brd, int row, int col)
{
    return Brd_is_rc_checked(brd, row + 1, col - 1, 'p') || Brd_is_rc_checked(brd, row + 1, col + 1, 'p');
}

static bool _attacked_bp(const Brd * brd, int row, int col)
{
    return Brd_is_rc_checked(brd, row - 1, col - 1, 'P') || Brd_is_rc_checked(brd, row - 1, col + 1, 'P');
}

static bool _attacked_pawn(const Brd * brd, int row, int col, CLR clr)
{
    return clr == CLR_W ? _attacked_wp(brd, row, col) : _attacked_bp(brd, row, col);
}

static bool _attacked_king(const Brd * brd, int row, int col, CLR clr)
{
    char king;

    king = _piece(KING_CSTR, clr);

    return  Brd_is_rc_checked(brd, row - 1, col - 1, king) ||
            Brd_is_rc_checked(brd, row - 1, col, king) ||
            Brd_is_rc_checked(brd, row - 1, col + 1, king) ||
            Brd_is_rc_checked(brd, row, col - 1, king) ||
            Brd_is_rc_checked(brd, row, col + 1, king) ||
            Brd_is_rc_checked(brd, row + 1, col - 1, king) ||
            Brd_is_rc_checked(brd, row + 1, col, king) ||
            Brd_is_rc_checked(brd, row + 1, col + 1, king);
}

static bool _attacked_knight(const Brd * brd, int row, int col, CLR clr)
{
    char knight;

    knight = _piece(KNIGHT_CSTR, clr);

    return  Brd_is_rc_checked(brd, row - 2, col - 1, knight) ||
            Brd_is_rc_checked(brd, row - 2, col - 1, knight) ||
            Brd_is_rc_checked(brd, row - 1, col - 2, knight) ||
            Brd_is_rc_checked(brd, row - 1, col + 2, knight) ||
            Brd_is_rc_checked(brd, row + 1, col - 2, knight) ||
            Brd_is_rc_checked(brd, row + 1, col + 2, knight) ||
            Brd_is_rc_checked(brd, row + 2, col - 1, knight) ||
            Brd_is_rc_checked(brd, row + 2, col - 1, knight);
}

#define $af_dir_gen(dir, dr, dc, p0, p1) \
static bool _attacked_ ## dir(const Brd * brd, int row, int col, CLR clr) \
{ \
    row += dr; \
    col += dc; \
 \
    while (_row_col_valid(row, col)) \
    { \
        if (_piece_clr(* Brd_get_rc(brd, row, col)) == _clr_invert(clr)) return false; \
        if (Brd_is_rc(brd, row, col, _piece(p0, clr)) || Brd_is_rc(brd, row, col, _piece(p1, clr))) return true; \
        row += dr; \
        col += dc; \
    } \
 \
    return false; \
}

$af_dir_gen(u, -1, 0, QUEEN_CSTR, ROOK_CSTR)
$af_dir_gen(d, 1, 0, QUEEN_CSTR, ROOK_CSTR)
$af_dir_gen(l, 0, -1, QUEEN_CSTR, ROOK_CSTR)
$af_dir_gen(r, 0, 1, QUEEN_CSTR, ROOK_CSTR)
$af_dir_gen(lu, -1, -1, QUEEN_CSTR, BISH_CSTR)
$af_dir_gen(ld, 1, -1, QUEEN_CSTR, BISH_CSTR)
$af_dir_gen(ru, -1, 1, QUEEN_CSTR, BISH_CSTR)
$af_dir_gen(rd, 1, 1, QUEEN_CSTR, BISH_CSTR)

bool Brd_attacked_rc(const Brd * brd, int row, int col, CLR clr)
{
    return  _attacked_pawn(brd, row, col, clr) ||
            _attacked_king(brd, row, col, clr) ||
            _attacked_knight(brd, row, col, clr) ||
            _attacked_u(brd, row, col, clr) ||
            _attacked_d(brd, row, col, clr) ||
            _attacked_l(brd, row, col, clr) ||
            _attacked_r(brd, row, col, clr) ||
            _attacked_lu(brd, row, col, clr) ||
            _attacked_ld(brd, row, col, clr) ||
            _attacked_ru(brd, row, col, clr) ||
            _attacked_rd(brd, row, col, clr);
}

int Brd_find_king(const Brd * brd, CLR clr)
{
    char king;

    king = _piece(KING_CSTR, clr);

    for (int k = 0; k < BRD_SIZE; k ++) if (Brd_is(brd, k, king)) return k;

    return NO_IDX;
}