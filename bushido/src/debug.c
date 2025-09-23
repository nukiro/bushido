#include "debug.h"

#include "common.h"
#include "types.h"
#include "debug.h"

int debug_init(Configuration *c)
{
    DBG("debug mode on");
    c->fov_view = 1;
    c->fov_zoom = 30.0f;
    c->window_height = 1920;
    c->window_width = 1080;
    c->navigation_scene_init = "A0001";
    return STATUS_OK;
}