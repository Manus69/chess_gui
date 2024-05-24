#include "_private.h"

BrdInfo BrdInfo_init(const Board * board)
{
    BrdInfo info = {};
    CLR     clr;
    char    piece;
    u64     mask;
    
    for (int k = 0; k < CHESS_BOARD_SIZE; k ++)
    {
        piece = Board_at(board, k);
        if (piece_none(piece)) continue;

        clr = piece_clr(piece);
        info.material[clr] += piece_value(piece);

        if (piece_king(piece)) info.king_idx[clr] = k;

        u64_set_bit(& info.square_mask[clr], k);

        mask = mask_attack_mask(board, k);
        info.attack_mask[clr] |= mask;
    }

    return info;
}

bool BrdInfo_square_attacked_by(const BrdInfo * pos_info, int idx, CLR clr)
{
    return mask_includes(pos_info->attack_mask[clr], idx);
}

bool BrdInfo_in_check(const BrdInfo * pos_info, CLR clr)
{
    return PosInfo_square_attacked_by(pos_info, pos_info->king_idx[CLR_invert(clr)], clr);
}