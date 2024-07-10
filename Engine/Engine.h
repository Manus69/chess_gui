#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>

typedef enum GAME_STS GAME_STS;

enum GAME_STS
{
    GAME_STS_OK,
    GAME_STS_NOK,
    GAME_STS_WIC,
    GAME_STS_BIC,
    GAME_STS_WW,
    GAME_STS_BW,
    GAME_STS_STLMT,
    GAME_STS_MAX,
};

typedef struct Game Game;

Game *      Game_new_from_cstr(const char * cstr);
Game *      Game_new(void);
void        Game_del(Game * game);
void        Game_reset(Game * game);
char *      Game_Brd_cstr(const Game * game);
bool        Game_try_move(Game * game, int from, int to);
GAME_STS    Game_get_STS(const Game * game);
GAME_STS    Game_engine_move(Game * game);

#endif