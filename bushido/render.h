#include <raylib.h>
#include <raymath.h>

#include "types.h"
#include "scene.h"
#include "nathan.h"

#pragma once

#define COLOR_BACKGROUND (Color){25, 25, 25, 1}
#define DEV_TOOL_FONT_SIZE 15
#define DEV_TOOL_MARGIN_X 10
#define DEV_TOOL_MARGIN_Y 10
#define DEV_TOOL_SEPARATOR 5
#define N " N "
#define E " E "
#define S " S "
#define W " W "
#define WE "W E"
#define EW "E W"
#define NS "N S"
#define SN "S N"

void render_origin()
{

    DrawLine3D((Vector3){-0.5f, 0.0f, -0.5f}, (Vector3){1.0f, 0.0f, -0.5f}, WHITE);
    DrawLine3D((Vector3){-0.5f, 0.0f, -0.5f}, (Vector3){-0.5f, 0.0f, 1.0f}, WHITE);
}

int _render_dev_position_y(int n)
{
    return DEV_TOOL_MARGIN_Y + ((DEV_TOOL_FONT_SIZE + DEV_TOOL_SEPARATOR) * n);
}

void _render_dev_tool_compass(Scene scene)
{
    switch (scene.facing)
    {
    case SCENE_FACING_NORTH:
        DrawText(N, GetScreenWidth() / 2 - MeasureText(N, DEV_TOOL_FONT_SIZE) / 2, _render_dev_position_y(0), DEV_TOOL_FONT_SIZE, LIME);
        DrawText(WE, GetScreenWidth() / 2 - MeasureText(WE, DEV_TOOL_FONT_SIZE) / 2, _render_dev_position_y(1), DEV_TOOL_FONT_SIZE, LIME);
        DrawText(S, GetScreenWidth() / 2 - MeasureText(S, DEV_TOOL_FONT_SIZE) / 2, _render_dev_position_y(2), DEV_TOOL_FONT_SIZE, LIME);
        break;
    case SCENE_FACING_SOUTH:
        DrawText(S, GetScreenWidth() / 2 - MeasureText(S, DEV_TOOL_FONT_SIZE) / 2, _render_dev_position_y(0), DEV_TOOL_FONT_SIZE, LIME);
        DrawText(EW, GetScreenWidth() / 2 - MeasureText(EW, DEV_TOOL_FONT_SIZE) / 2, _render_dev_position_y(1), DEV_TOOL_FONT_SIZE, LIME);
        DrawText(N, GetScreenWidth() / 2 - MeasureText(N, DEV_TOOL_FONT_SIZE) / 2, _render_dev_position_y(2), DEV_TOOL_FONT_SIZE, LIME);
        break;
    case SCENE_FACING_EAST:
        DrawText(E, GetScreenWidth() / 2 - MeasureText(E, DEV_TOOL_FONT_SIZE) / 2, _render_dev_position_y(0), DEV_TOOL_FONT_SIZE, LIME);
        DrawText(NS, GetScreenWidth() / 2 - MeasureText(NS, DEV_TOOL_FONT_SIZE) / 2, _render_dev_position_y(1), DEV_TOOL_FONT_SIZE, LIME);
        DrawText(W, GetScreenWidth() / 2 - MeasureText(W, DEV_TOOL_FONT_SIZE) / 2, _render_dev_position_y(2), DEV_TOOL_FONT_SIZE, LIME);
        break;
    case SCENE_FACING_WEST:
        DrawText(W, GetScreenWidth() / 2 - MeasureText(W, DEV_TOOL_FONT_SIZE) / 2, _render_dev_position_y(0), DEV_TOOL_FONT_SIZE, LIME);
        DrawText(SN, GetScreenWidth() / 2 - MeasureText(SN, DEV_TOOL_FONT_SIZE) / 2, _render_dev_position_y(1), DEV_TOOL_FONT_SIZE, LIME);
        DrawText(E, GetScreenWidth() / 2 - MeasureText(E, DEV_TOOL_FONT_SIZE) / 2, _render_dev_position_y(2), DEV_TOOL_FONT_SIZE, LIME);
        break;
    }
}

void render_dev_tool(Scene scene)
{
    // UP-LEFT
    DrawText(TextFormat("Camera facing: %d", scene.facing), DEV_TOOL_MARGIN_X, _render_dev_position_y(0), DEV_TOOL_FONT_SIZE, LIME);
    DrawText(TextFormat("Nathan: x=%.2f z=%.2f", scene.nathan.position.x, scene.nathan.position.z), DEV_TOOL_MARGIN_X, _render_dev_position_y(1), DEV_TOOL_FONT_SIZE, LIME);

    // UP-RIGHT
    _render_dev_tool_compass(scene);
}

void render(Scene scene, Camera3D camera)
{
    BeginDrawing();
    ClearBackground(COLOR_BACKGROUND);

    BeginMode3D(camera);

    scene_navigation_render(scene);

    nathan_render(scene.nathan);

#ifdef DEBUG
    render_origin();
#endif

    EndMode3D();

#ifdef DEBUG
    render_dev_tool(scene);
#endif

    EndDrawing();
}