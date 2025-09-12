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

void window_loop(void (*update)(NavigationScene *, Camera3D *, float), void (*render)(NavigationScene, Camera3D))
{
    NavigationScene scene = scene_init();
    scene.nathan = nathan_init((Vector3){0.0f, 0.0f, 0.0f});

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