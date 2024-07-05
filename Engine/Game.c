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

Game * Game_new_from_cstr(const char * cstr)
{
    Game *  game;
    Pos     pos;

    if (! Pos_init_cstr(& pos, cstr))           return NULL;
    if (! (game = calloc(1, sizeof(* game))))   return NULL;
    
    game->pos = pos;
    game->moven = 0;

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
    Pos_init_cstr(& game->pos, BRD_CSTR_DFLT);
    game->moven = 0;
}

char * Game_get_cstr(const Game * game)
{
    return Pos_get_cstr(& game->pos);
}

bool Game_try_move(Game * game, int from, int to)
{
    Pos next;

    if (Pos_move(& game->pos, & next, from, to))
    {
        game->pos = next;
        game->moven ++;

        return true;
    }

    return false;
}