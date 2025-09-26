#include "window.h"

#include <raylib.h>

#include "types.h"
#include "render.h"
#include "config.h"
#include "debug.h"

void window_init(const Game *g, Manager *m, const Configuration *c)
{
    InitWindow(m->window.width, m->window.height, g->title);
    SetWindowTitle(m->window.title);
    SetTargetFPS(c->fps);
    DBG("window '%s' titled as %s, open: %dx%d", g->title, m->window.title, m->window.width, m->window.height);
    DBG("game fps: %d", c->fps);
}

void window_loop(Manager *m)
{
    DBG("window loop start");
    while (!WindowShouldClose())
    {
        render(m);
    }
    DBG("window loop end");
}

void window_close()
{
    CloseWindow();
    DBG("window closed");
}