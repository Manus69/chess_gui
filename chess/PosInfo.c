#include "_private.h"

PosInfo PosInfo_init(const Position * position)
{
    PosInfo pos_info = {};
    CLR     clr;
    char    piece;
    u64     mask;
    
    for (int k = 0; k < CHESS_BOARD_SIZE; k ++)
    {
        piece = Board_at(& position->board, k);
        if (piece_none(piece)) continue;

        clr = piece_clr(piece);
        pos_info.material[clr] += piece_value(piece);

        if (piece_king(piece)) pos_info.king_idx[clr] = k;

        mask = mask_attack_mask(& position->board, k);
        pos_info.attack_mask[clr] |= mask;
    }

    return pos_info;
}

bool PosInfo_in_check(const PosInfo * pos_info, CLR clr)
{
    return mask_includes(pos_info->attack_mask[CLR_invert(clr)], pos_info->king_idx[clr]);
}