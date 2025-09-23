#include "debug.h"

#include "common.h"
#include "types.h"
#include "debug.h"
#include "config.h"

int debug_init(Configuration *c)
{
    DBG("debug mode on");

    c->fps = GAME_FPS;
    c->assets = GAME_PATH_ASSETS;
    c->fov_view = 1;
    c->fov_zoom = 30.0f;
    c->window_width = 1920;
    c->window_height = 1080;
    c->navigation_scene_init = GAME_NAVIGATION_SCENE_INIT;

    return STATUS_OK;
}