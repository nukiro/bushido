#pragma once

#include <raylib.h>
#include <raymath.h>

#include "types.h"
#include "logger.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define FPS 60

void window_init(Game game)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, game.title);
    SetTargetFPS(FPS);
}

void window_loop(Game *game, void (*update)(Scene *, Camera3D *, float), void (*render)(Scene, Camera3D))
{
    Scene *sp = &game->scene;
    Camera3D *cp = &game->camera;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        update(sp, cp, dt);
        render(*sp, *cp);
    }
}

void window_close()
{
    CloseWindow();
}