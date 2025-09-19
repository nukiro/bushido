#include "window.h"

void window_init(const Game *g, Manager *m)
{
    InitWindow(m->window.width, m->window.height, g->title);
    SetWindowTitle(m->window.title);
    SetTargetFPS(GAME_FPS);
    DBG("window %s open: %dx%d", g->title, m->window.width, m->window.height);
    DBG("game fps: %d", GAME_FPS);
}

void window_loop()
{
    DBG("window loop start");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground((Color){25, 25, 25, 1});
        EndDrawing();
    }
    DBG("window loop end");
}

void window_close()
{
    CloseWindow();
    DBG("window closed");
}