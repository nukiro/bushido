#include <raylib.h>

#include "nathan.h"

#include <stdio.h>

#pragma once

#define ACTION_MATRIX 7
#define NAVIGATION_BOXES ACTION_MATRIX - 2

typedef struct Scene
{
    Nathan nathan;
    int navigation[ACTION_MATRIX][ACTION_MATRIX];
} Scene;

Scene scene_init()
{
    Scene scene = {0};

    scene.navigation[3][3] = 1;

    return scene;
}

void _scene_render_ground(float x, float z)
{
    DrawCube((Vector3){x, -0.05f, z}, 1.0f, 0.1f, 1.0f, (Color){0, 153, 76, 50});
    DrawCubeWires((Vector3){x, -0.05f, z}, 1.0f, 0.1f, 1.0f, (Color){255, 255, 255, 50});
}

void _scene_render_obstacle(float x, float z)
{
    DrawCube((Vector3){x, 0.5f, z}, 1.0f, 1.0f, 1.0f, (Color){102, 51, 0, 150});
    DrawCubeWires((Vector3){x, 0.5f, z}, 1.0f, 1.0f, 1.0f, (Color){255, 255, 255, 50});
}

void scene_navigation_render(Scene scene)
{
    for (int i = 1; i <= NAVIGATION_BOXES; i++)
    {
        for (int j = 1; j <= NAVIGATION_BOXES; j++)
        {
            switch (scene.navigation[i][j])
            {
            case 1:
                _scene_render_obstacle(i, j);
                break;
            }

            _scene_render_ground(i, j);
        }
    }
}