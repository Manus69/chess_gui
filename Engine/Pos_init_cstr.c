#include "_private.h"

static int _get_binc(bool * x, const char * cstr)
{
    if (* cstr == '0')
    {
        * x = false;
        return 1;
    }
    if (* cstr == '1')
    {
        * x = true;
        return 1;
    }

    return 0;
}

static int _get_CstlData(CstlData * cd, const char * cstr)
{
    if (* cstr ++ != ' ') return NO_IDX;

    if (_get_binc(& cd->lr_moved, cstr) != 1) return NO_IDX;
    cstr ++;

    if (_get_binc(& cd->king_moved, cstr) != 1) return NO_IDX;
    cstr ++;

    if (_get_binc(& cd->rr_moved, cstr) != 1) return NO_IDX;

    return 4;
}

static int _get_int_int(int_int * x, const char * cstr)
{
    int     len;
    char *  start;

    start = (char *) cstr;
    if (* cstr ++ != ' ') return NO_IDX;

    if ((len = cstr_parse_int(cstr, & x->a)) <= 0) return NO_IDX;
    cstr += len;

    if (* cstr ++ != ' ') return NO_IDX;
    if ((len = cstr_parse_int(cstr, & x->b)) <= 0) return NO_IDX;
    cstr += len;

    if (x->a < NO_IDX || x->a >= BRD_SIZE) return NO_IDX;
    if (x->b < NO_IDX || x->b >= BRD_SIZE) return NO_IDX;

    return cstr - start;
}

static bool _Pos_from_cstr(Pos * pos, const char * cstr)
{
    Brd         brd;
    CstlData    cdw;
    CstlData    cdb;
    int_int     last_move;
    CLR         move_clr;
    int         len;

    brd = Brd_init_cstr(cstr);
    cstr += BRD_SIZE;

    if ((len = _get_CstlData(& cdw, cstr)) <= 0) return false;
    cstr += len;

    if ((len = _get_CstlData(& cdb, cstr)) <= 0) return false;
    cstr += len;

    if ((len = _get_int_int(& last_move, cstr)) <= 0) return false;
    cstr += len;

    move_clr = last_move.b == NO_IDX ? CLR_W : _piece_clr(* Brd_get(& brd, last_move.b));

    * pos = Pos_init(brd, cdw, cdb, last_move, move_clr);

    return true;
}

static bool _Pos_from_cstr64(Pos * pos, const char * cstr)
{
    Brd brd;

    brd = Brd_init_cstr(cstr);
    * pos = Pos_init_default(brd);

    return true;
}

bool Pos_from_cstr(Pos * pos, const char * cstr)
{
    int len;

    if ((len = strlen(cstr)) < BRD_SIZE)    return false;
    if (len == BRD_SIZE)                    return _Pos_from_cstr64(pos, cstr);

    return _Pos_from_cstr(pos, cstr);
}