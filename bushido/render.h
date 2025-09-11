#include "raylib.h"

#pragma once

#define COLOR_BACKGROUND (Color){25, 25, 25, 1}

void render(Camera3D camera)
{
    BeginDrawing();
    ClearBackground(COLOR_BACKGROUND);

    BeginMode3D(camera);

    DrawLine3D((Vector3){-0.5f, 0.0f, -0.5f}, (Vector3){1.0f, 0.0f, -0.5f}, WHITE);
    DrawLine3D((Vector3){-0.5f, 0.0f, -0.5f}, (Vector3){-0.5f, 0.0f, 1.0f}, WHITE);

    EndMode3D();

    EndDrawing();
}