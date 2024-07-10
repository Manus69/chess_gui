#include "_private.h"

#include <stdio.h>

void dbg_msg(const char * msg, const char * file, int line)
{
    printf("%s %d : %s\n", file, line, msg);
}

void dbg_mask(u64 mask)
{
    char x;

    for (int row = 0; row < SIDE; row ++)
    {
        for (int col = 0; col < SIDE; col ++)
        {
            x = bits_bit(mask, _row_col_idx(row, col)) ? 'x' : '_';
            printf("%c", x);
        }
        $nl;
    }
}

void dbg_Pos(const Pos * pos)
{
    printf("%.*s ", BRD_SIZE, Pos_Brd_cstr(pos));
    printf("%d%d%d ", pos->cstl_data[CLR_W].lr_moved, pos->cstl_data[CLR_W].king_moved, pos->cstl_data[CLR_W].rr_moved);
    printf("%d%d%d ", pos->cstl_data[CLR_B].lr_moved, pos->cstl_data[CLR_B].king_moved, pos->cstl_data[CLR_B].rr_moved);
    printf("%d %d\n", pos->last_move.a, pos->last_move.b);
}

void dbg_move(char_char mv)
{
    printf("(%d - %d) ", mv.a, mv.b);
}

void dbg_movef(void * mv)
{
    dbg_move($(char_char) mv);
}