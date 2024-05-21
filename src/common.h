#ifndef COMMON_H
#define COMMON_H

#define     LIB_PATH "/home/manus/Documents/projects/libY/libY.h"
#include    LIB_PATH

#define     COMMON_BOARD_SIDE (8)
#define     COMMON_BOARD_SIZE (COMMON_BOARD_SIDE * COMMON_BOARD_SIDE)

typedef struct Move Move;

struct Move
{
    char from;
    char to;
};

static inline Move Move_init(char from, char to)
{
    return (Move)
    {
        .from = from,
        .to = to,
    };
}

static inline Move Move_init_no_move(void)
{
    return Move_init(NO_IDX, NO_IDX);
}

static inline bool Move_valid(Move mv)
{
    return ! (mv.from == NO_IDX && mv.to == NO_IDX);
}

static inline int _idx_row(int idx)
{
    return idx / COMMON_BOARD_SIDE;
}

static inline int _idx_col(int idx)
{
    return idx % COMMON_BOARD_SIDE;
}

static inline int _row_col_idx(int row, int col)
{
    return row * COMMON_BOARD_SIDE + col;
}



#endif