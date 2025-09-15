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
    snprintf(g.code, sizeof g.code, "%s", "A0001");

    g.scene = scene_init(g, SCENE_FACING_NORTH);
    g.camera = camera_init(&g.scene);

    return g;
}

void game_close_scene(Game *game)
{
    snprintf(game->code, sizeof game->code, "%s", scene_destination(&game->scene));
    // game->code = scene_destination(&game->scene);
    log_info("new destination in game: %s", game->code);
    scene_free(&game->scene);
    log_info("new destination in game: %s", game->code);
    // game->code = "A0001";
}

void game_init_scene(Game *g, const char *code)
{
    log_info("init ?? %s", g->code);
    // snprintf(g->code, sizeof g->code, "%s", code);
    g->scene = scene_init(*g, SCENE_FACING_NORTH);
    g->camera = camera_init(&g->scene);
}