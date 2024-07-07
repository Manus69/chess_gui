#include "_private.h"

#define BRD_CSTR_DFLT \
"RNBQKBNR" \
"PPPPPPPP" \
"________" \
"________" \
"________" \
"________" \
"pppppppp" \
"rnbqkbnr"

static void _init(Game * game, Pos pos)
{
    game->pos_initial = pos;
    game->pos = pos;
    game->moven = 0;
}

Game * Game_new_from_cstr(const char * cstr)
{
    Game *  game;
    Pos     pos;

    if (! cstr) cstr = BRD_CSTR_DFLT;
    
    if (! Pos_from_cstr(& pos, cstr))           return NULL;
    if (! (game = calloc(1, sizeof(* game))))   return NULL;
    
    _init(game, pos);

    return game;
}

Game * Game_new(void)
{
    return Game_new_from_cstr(BRD_CSTR_DFLT);
}

void Game_del(Game * game)
{
    free(game);
}

void Game_reset(Game * game)
{
    _init(game, game->pos_initial);
}

char * Game_Brd_cstr(const Game * game)
{
    return Pos_Brd_cstr(& game->pos);
}

bool Game_try_move(Game * game, int from, int to)
{
    Pos next;

    if (Pos_try_move(& game->pos, & next, from, to))
    {
        game->pos = next;
        game->moven ++;

        //
        dbg_Pos(& game->pos);
        //

        return true;
    }

    return false;
}