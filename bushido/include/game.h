#pragma once

#include "status.h"

typedef struct Game
{
    const char *tag;     // code repository version use to build the game
    const char *release; // game build version
    const char *title;
} Game;

status game_init(Game *game);
void game_close();
