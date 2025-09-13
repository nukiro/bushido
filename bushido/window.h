#include <raylib.h>
#include <raymath.h>

#include "types.h"
#include "scene.h"
#include "nathan.h"
#include "camera.h"

#pragma once

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define FPS 60

void window_init()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "武士道");
    SetTargetFPS(FPS);
}

void window_loop(void (*update)(Scene *, Camera3D *, float), void (*render)(Scene, Camera3D))
{
    Scene scene = scene_init(-1);
    Camera3D camera = camera_init(&scene);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        update(&scene, &camera, dt);
        render(scene, camera);
    }
}

void window_close()
{
    CloseWindow();
}