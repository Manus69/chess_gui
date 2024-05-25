#include "_private.h"

#define SEP ' '

static void _add_castle_info(Str * str, byte ci)
{
    for (int k = 0; k < 3; k ++)
    {
        Str_push_byte(str, u64_bit(ci, k) ? '1' : '0');
    }
}

Str Position_to_Str(const Position * position)
{
    Str str;

    str = Str_ctor_empty(2 * CHESS_BOARD_SIZE);
    Str_push_mem(& str, Position_Board_cstr(position), CHESS_BOARD_SIZE);
    Str_push_byte(& str, SEP);

    i32_to_Str(& str, position->last_move.from);
    Str_push_byte(& str, SEP);

    i32_to_Str(& str, position->last_move.to);
    Str_push_byte(& str, SEP);

    _add_castle_info(& str, position->castle_info[CLR_WHITE]);
    Str_push_byte(& str, SEP);
    _add_castle_info(& str, position->castle_info[CLR_BALCK]);

    return str;
}

Position Position_init_Str(const Str * str)
{
    Position    pos;
    Slc         slc;
    Slc         current;

    slc = Str_as_Slc(str);

    current = Slc_split_next(& slc, SEP);
    pos.board = Board_init_cstr(Slc_start(current));

    current = Slc_split_next(& slc, SEP);
    i32_parse_Slc((i32 *) & pos.last_move.from, current);

    current = Slc_split_next(& slc, SEP);
    i32_parse_Slc((i32 *) & pos.last_move.to, current);

    current = Slc_split_next(& slc, SEP);
    u64_parse_bin_cstr_len((u64 *) & pos.castle_info[CLR_WHITE], Slc_start(current), Slc_size(current));

    current = Slc_split_next(& slc, SEP);
    u64_parse_bin_cstr_len((u64 *) & pos.castle_info[CLR_BALCK], Slc_start(current), Slc_size(current));

    return pos;
}