#include "_private.h"

static bool _find_attacker_in_dir(const Board * board, int row, int col, CLR clr, int drow, int dcol, bool (* f)(char))
{
    char square;

    row += drow;
    col += dcol;

    while (_row_col_valid(row, col))
    {
        square = Board_at_rc(board, row, col);
        if (piece_none(square))
        {
            row += drow;
            col += dcol;
        }
        else if (piece_clr(square) == CLR_invert(clr))  return false;
        else if (f(square))                             return true;
        else                                            return false;        
    }

    return false;
}

static bool _find_attacker_in_row(const Board * board, int row, int col, CLR clr)
{
    return _find_attacker_in_dir(board, row, col, clr, 0, -1, piece_rook_or_queen) || 
            _find_attacker_in_dir(board, row, col, clr, 0, 1, piece_rook_or_queen);
}

static bool _find_attacker_in_col(const Board * board, int row, int col, CLR clr)
{
    return _find_attacker_in_dir(board, row, col, clr, -1, 0, piece_rook_or_queen) ||
            _find_attacker_in_dir(board, row, col, clr, 1, 0, piece_rook_or_queen);
}

static bool _find_attacker_in_diag(const Board * board, int row, int col, CLR clr)
{
    return _find_attacker_in_dir(board, row, col, clr, -1, -1, piece_bishop_or_queen) ||
            _find_attacker_in_dir(board, row, col, clr, 1, 1, piece_bishop_or_queen) ||
            _find_attacker_in_dir(board, row, col, clr, -1, 1, piece_bishop_or_queen) ||
            _find_attacker_in_dir(board, row, col, clr, 1, -1, piece_bishop_or_queen);
}

static bool _is_knight(const Board * board, int row, int col, CLR clr)
{
    return _row_col_valid(row, col) && piece_knight_clr(Board_at_rc(board, row, col), clr);
}

static bool _is_king(const Board * board, int row, int col, CLR clr)
{
    return _row_col_valid(row, col) && piece_king_clr(Board_at_rc(board, row, col), clr);
}

static bool _is_pawn(const Board * board, int row, int col, CLR clr)
{
    return _row_col_valid(row, col) && piece_pawn_clr(Board_at_rc(board, row, col), clr);
}

static bool _find_attacker_knight(const Board * board, int row, int col, CLR clr)
{
    return _is_knight(board, row - 2, col - 1, clr) ||
            _is_knight(board, row - 2, col + 1, clr) ||
            _is_knight(board, row - 1, col - 2, clr) ||
            _is_knight(board, row - 1, col + 2, clr) ||
            _is_knight(board, row + 1, col - 2, clr) ||
            _is_knight(board, row + 1, col + 2, clr) ||
            _is_knight(board, row + 2, col - 1, clr) ||
            _is_knight(board, row + 2, col + 1, clr);
}

static bool _find_attacker_king(const Board * board, int row, int col, CLR clr)
{
    return _is_king(board, row - 1, col - 1, clr) ||
            _is_king(board, row - 1, col, clr) ||
            _is_king(board, row - 1, col + 1, clr) ||
            _is_king(board, row, col - 1, clr) ||
            _is_king(board, row, col + 1, clr) ||
            _is_king(board, row + 1, col - 1, clr) ||
            _is_king(board, row + 1, col, clr) ||
            _is_king(board, row + 1, col + 1, clr);
}

static bool _find_attacker_pawn(const Board * board, int row, int col, CLR clr)
{
    if (clr == CLR_WHITE)
    {
        return _is_pawn(board, row + 1, col - 1, clr) ||
                _is_pawn(board, row + 1, col + 1, clr);
    }
    else
    {
        return _is_pawn(board, row - 1, col - 1, clr) ||
                _is_pawn(board, row - 1, col + 1, clr);
    }

}

bool Board_square_attacked_by(const Board * board, int idx, CLR clr)
{
    int row, col;

    row = _idx_row(idx);
    col = _idx_col(idx);

    return _find_attacker_in_row(board, row, col, clr) ||
            _find_attacker_in_col(board, row, col, clr) ||
            _find_attacker_in_diag(board, row, col, clr) ||
            _find_attacker_knight(board, row, col, clr) ||
            _find_attacker_pawn(board, row, col, clr) ||
            _find_attacker_king(board, row, col, clr);
}