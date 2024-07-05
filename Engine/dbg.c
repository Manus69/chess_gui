#include "_private.h"

#include <stdio.h>

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