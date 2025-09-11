#include <raylib.h>
#include <raymath.h>

#pragma once

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define FPS 60

void window_init()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "武士道");
    SetTargetFPS(FPS);
}

void window_loop(void (*update)(float), void (*render)(Camera3D camera))
{
    Vector3 nathan = {1.0f, 0.0f, 1.0f};

    Camera3D camera = {0};
    camera.position = Vector3Add(nathan, (Vector3){-10.0f, 10.0f, -10.0f});
    camera.target = Vector3Add(nathan, (Vector3){0.0f, 1.0f, 0.0f});
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 10.0f;
    camera.projection = CAMERA_ORTHOGRAPHIC;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        update(dt);
        render(camera);
    }
}

void window_close()
{
    CloseWindow();
}