#include <raylib.h>
#include <raymath.h>

#include "scene.h"
#include "nathan.h"

#pragma once

#define COLOR_BACKGROUND (Color){25, 25, 25, 1}

void render_origin()
{

    DrawLine3D((Vector3){-0.5f, 0.0f, -0.5f}, (Vector3){1.0f, 0.0f, -0.5f}, WHITE);
    DrawLine3D((Vector3){-0.5f, 0.0f, -0.5f}, (Vector3){-0.5f, 0.0f, 1.0f}, WHITE);
}

void render_dev_tools(Scene scene)
{
    DrawText(TextFormat("Nathan: x=%.2f z=%.2f", scene.nathan.position.x, scene.nathan.position.z), 10, 10, 15, LIME);
}

void render(Scene scene, Camera3D camera)
{
    BeginDrawing();
    ClearBackground(COLOR_BACKGROUND);

    BeginMode3D(camera);

    scene_navigation_render();

    nathan_render(scene.nathan);

#ifdef DEBUG
    render_origin();
#endif

    EndMode3D();

#ifdef DEBUG
    render_dev_tools(scene);
#endif

    EndDrawing();
}