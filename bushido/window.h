#pragma once

#include <raylib.h>
#include <raymath.h>

#include "types.h"
#include "logger.h"
#include "game.h"

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
        if (sp->is_ready && sp->is_done)
        {
            // char *next_scene = sp->doors[sp->to];
            game_close_scene(game);
            log_info("navigation to: %s", game->code);
            game_init_scene(game, game->code);
        }

        if (sp->is_ready && !sp->is_done)
        {
            update(sp, cp, dt);
            render(*sp, *cp);
        }
        else
        {
            BeginDrawing();
            ClearBackground((Color){25, 25, 25, 1});

            BeginMode3D(*cp);

            EndMode3D();

            EndDrawing();
        }
    }
}

void window_close()
{
    CloseWindow();
}