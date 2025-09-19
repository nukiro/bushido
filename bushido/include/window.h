#pragma once

#include <raylib.h>

#include "debug.h"
#include "game.h"
#include "manager.h"
#include "render.h"

void window_init(const Game *game, Manager *manager);
void window_loop(const Game *game, Manager *manager);
void window_close();