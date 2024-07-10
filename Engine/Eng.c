#include "_private.h"

#define MVDC (1 << 8)

bool Eng_init(Eng * eng)
{
    * eng = (Eng){};

    if (! Vec_init(& eng->move_vec, NULL, sizeof(char_char), MVDC, 0)) return false;

    return true;
}

Eng * Eng_new(void)
{
    Eng * eng;

    if (! (eng = mem_alloc0(sizeof(* eng), 1))) return NULL;
    if (! Eng_init(eng))                        return NULL;

    return eng;
}

void Eng_del(Eng * eng)
{
    Vec_del(& eng->move_vec);
    mem_del(eng);
}

static int _mask_to_moves(int from, u64 mask, Vec * moves)
{
    char_char move;

    for (int k = 0; k < BRD_SIZE; k ++)
    {
        if (bits_bit(mask, k))
        {
            move = (char_char)
            {
                .a = from,
                .b = k,
            };

            Vec_push(moves, & move);
        }
    }

    return bits_popcount(mask);
}

Vec * Eng_get_moves_square(Eng * engine, const Pos * pos, int idx)
{
    u64 mask;

    mask = Pos_compute_mmask(pos, idx);
    _mask_to_moves(idx, mask, & engine->move_vec);

    return & engine->move_vec;
}

Vec * Eng_get_moves_CLR(Eng * engine, const Pos * pos, CLR clr)
{
    for (int from = 0; from < BRD_SIZE; from ++)
    {
        if (Brd_is_CLR(& pos->brd, from, clr))
        {
            Eng_get_moves_square(engine, pos, from);
        }
    }

    return & engine->move_vec;
}

Vec * Eng_get_moves(Eng * eng, const Pos * pos)
{
    CLR clr;

    clr = Pos_turn(pos);

    return Eng_get_moves_CLR(eng, pos, clr);
}

void Eng_movevec_reset(Eng * eng)
{
    Vec_pop_all(& eng->move_vec);
}

i32 Eng_movevec_len(const Eng * eng)
{
    return Vec_len(& eng->move_vec);
}