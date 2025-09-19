#pragma once

#include <raylib.h>

#include "game.h"
#include "manager.h"

#define RENDER_COLOR_BACKGROUND (Color){25, 25, 25, 1}

void render(Game *g, Manager *manager);