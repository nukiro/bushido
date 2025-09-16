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
    // initial scene
    snprintf(g.code, sizeof g.code, "%s", "A0001");
    // set naviation as zero
    snprintf(g.from, sizeof g.from, "%s", "00000");

    g.scene = scene_init(g, SCENE_FACING_NORTH);
    g.camera = camera_init(&g.scene);

    return g;
}

void game_close_scene(Game *game)
{
    // update game next scene and previous scene
    snprintf(game->from, sizeof game->from, "%s", game->code);
    snprintf(game->code, sizeof game->code, "%s", scene_destination(&game->scene));
    // free previous scene before loading the next one
    scene_free(&game->scene);
}

void game_init_scene(Game *g)
{
    g->scene = scene_init(*g, SCENE_FACING_NORTH);
    g->camera = camera_init(&g->scene);
}