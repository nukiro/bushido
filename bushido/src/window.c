#include "window.h"

void window_init(const Game *g, Manager *m)
{
    InitWindow(m->window.width, m->window.height, g->title);
    SetWindowTitle(m->window.title);
    SetTargetFPS(g->config.fps);
    DBG("window '%s', title %s, resolution: %dx%d", g->title, m->window.title, m->window.width, m->window.height);
    DBG("game fps: %d", GAME_FPS);
}

void window_loop(const Game *g, Manager *m)
{
    DBG("window loop start");
    while (!WindowShouldClose())
    {
        render(g, m);
    }
    DBG("window loop end");
}

void window_close()
{
    CloseWindow();
    DBG("window closed");
}