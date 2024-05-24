#include "_private.h"

#include <stdio.h>

void dbg_mask(u64 mask)
{
    char    buff[CHESS_BOARD_SIDE + 1] = {};
    int     idx;

    for (int row = 0; row < CHESS_BOARD_SIDE; row ++)
    {
        idx = 0;
        for (int col = 0; col < CHESS_BOARD_SIDE; col ++)
        {
            buff[idx] = mask_includes(mask, _row_col_idx(row, col)) ? 'x' : '_';
            idx ++;
        }

        printf("%s", buff);
        nl_;
    }
}

void dbg_Board(const Board * board)
{
    for (int k = 0; k < CHESS_BOARD_SIZE; k ++)
    {
        printf("%c", Board_at(board, k));

        if (k % CHESS_BOARD_SIDE == 0 && k > 0) nl_;
    }
}

void dbg_BrdInfo(const BrdInfo * pi)
{
    dbg_mask(pi->attack_mask[CLR_WHITE]);
    nl_;
    dbg_mask(pi->attack_mask[CLR_BALCK]);
}


