#include "_private.h"

static bool _mv_is_castle(const Position * pos, Move mv)
{
    return piece_king(Board_at(& pos->board, mv.from)) && 
            (Board_col_distance(_idx_col(mv.from), _idx_col(mv.to)) == 2);
}

static bool _mv_is_short_castle(const Position * pos, Move mv)
{
    return _mv_is_castle(pos, mv) && 
            (_idx_col(mv.to) > _idx_col(mv.from));
}

static bool _mv_is_long_castle(const Position * pos, Move mv)
{
    return _mv_is_castle(pos, mv) && 
            (_idx_col(mv.to) < _idx_col(mv.from));
}

static bool _mv_is_promotion(const Position * pos, Move mv)
{
    return piece_pawn(Board_at(& pos->board, mv.from)) &&
        (_idx_row(mv.to) == 0 || _idx_row(mv.to) == CHESS_BOARD_SIDE - 1);
}

static bool _mv_is_en_passant(const Position * pos, Move mv)
{
    return piece_pawn(Board_at(& pos->board, mv.from)) && 
            _idx_col(mv.from) != _idx_col(mv.to) &&
            Board_square_empty(& pos->board, mv.to);
}

static bool _mv_is_king_move(const Position * pos, Move mv)
{
    return piece_king(Board_at(& pos->board, mv.from));
}

static bool _mv_is_rook_move(const Position * pos, Move mv)
{
    return piece_rook(Board_at(& pos->board, mv.from));
}

static void _apply_short_castle(Position * pos, Move mv)
{
    int rook_from;
    int rook_to;
    int row;
    CLR clr;

    clr = Board_square_piece_clr(& pos->board, mv.from);
    row = _idx_row(mv.from);
    rook_from = _row_col_idx(row, CHESS_BOARD_SIDE - 1);
    rook_to = _row_col_idx(row, _idx_col(mv.from) + 1);

    Board_move_Move(& pos->board, mv);
    Board_move(& pos->board, rook_from, rook_to);

    castle_info_move_king(& pos->castle_info[clr]);
    castle_info_move_rookh(& pos->castle_info[clr]);
}

static void _apply_long_castle(Position * pos, Move mv)
{
    int rook_from;
    int rook_to;
    int row;
    CLR clr;

    clr = Board_square_piece_clr(& pos->board, mv.from);
    row = _idx_row(mv.from);
    rook_from = _row_col_idx(row, 0);
    rook_to = _row_col_idx(row, _idx_col(mv.from) - 1);

    Board_move_Move(& pos->board, mv);
    Board_move(& pos->board, rook_from, rook_to);

    castle_info_move_king(& pos->castle_info[clr]);
    castle_info_move_rooka(& pos->castle_info[clr]);
}

static void _apply_en_passant(Position * pos, Move mv)
{
    int row, col;

    row = _idx_row(mv.from);
    col = _idx_col(mv.to);

    Board_set(& pos->board, _row_col_idx(row, col), CHESS_PIECE_NONE);
    Board_move_Move(& pos->board, mv);
}

static void _apply_promotion(Position * pos, Move mv)
{
    char piece;

    piece = _idx_row(mv.to) == 0 ? CHESS_PIECE_WQ : CHESS_PIECE_BQ;

    Board_move_Move(& pos->board, mv);
    Board_set(& pos->board, mv.to, piece);
}

static void _apply_king_move(Position * pos, Move mv)
{
    castle_info_move_king(& pos->castle_info[Board_square_piece_clr(& pos->board, mv.from)]);
    Board_move_Move(& pos->board, mv);
}

static void _apply_rook_move(Position * pos, Move mv)
{
    CLR clr;

    clr = Board_square_piece_clr(& pos->board, mv.from);

    if (_idx_col(mv.from) == 0)                         castle_info_move_rooka(& pos->castle_info[clr]);
    else if (_idx_col(mv.from) == CHESS_BOARD_SIDE - 1) castle_info_move_rookh(& pos->castle_info[clr]);

    Board_move_Move(& pos->board, mv);
}

void Position_apply_move(Position * pos, Move mv)
{
    if (_mv_is_short_castle(pos, mv))       _apply_short_castle(pos, mv);
    else if (_mv_is_long_castle(pos, mv))   _apply_long_castle(pos, mv);
    else if (_mv_is_en_passant(pos, mv))    _apply_en_passant(pos, mv);
    else if (_mv_is_promotion(pos, mv))     _apply_promotion(pos, mv);
    else if (_mv_is_king_move(pos, mv))     _apply_king_move(pos, mv);
    else if (_mv_is_rook_move(pos, mv))     _apply_rook_move(pos, mv);
    else                                    Board_move_Move(& pos->board, mv);

    pos->last_move = mv;
}