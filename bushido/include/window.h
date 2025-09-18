#pragma once

#include <raylib.h>

#include "debug.h"
#include "game.h"
#include "manager.h"

void window_init(const Game *g, Manager *m);
void window_loop();
void window_close();