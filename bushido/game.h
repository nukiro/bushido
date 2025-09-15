#pragma once

#include <raylib.h>

#include "logger.h"
#include "scene.h"
#include "camera.h"
#include "types.h"

Game game_init()
{
    log_info("initializing game...");
    Game g = {0};
    g.title = "武士道";
    g.path = "maps/";
    g.code = "A0001";

    g.scene = scene_init(g, SCENE_FACING_NORTH);
    g.camera = camera_init(&g.scene);

    return g;
}

void game_close(Game *game)
{

    scene_free(&game->scene);
}