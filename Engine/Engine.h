#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>

typedef struct Game Game;

Game *  Game_new_from_cstr(const char * cstr);
Game *  Game_new(void);
void    Game_del(Game * game);
void    Game_reset(Game * game);
char *  Game_get_cstr(const Game * game);
bool    Game_try_move(Game * game, int from, int to);


#endif