#include <raylib.h>

#include "nathan.h"

#include <stdio.h>

#pragma once

#define NAVIGATION_BOXES 5
#define NAVIGATION_MATRIX 7

typedef struct Scene
{
    Nathan nathan;
    int navigation[NAVIGATION_MATRIX][NAVIGATION_MATRIX];
} Scene;

Scene scene_init()
{
    Scene scene = {0};
    return scene;
}

void scene_navigation_render()
{
    for (int i = 1; i <= NAVIGATION_BOXES; i++)
    {
        for (int j = 1; j <= NAVIGATION_BOXES; j++)
        {
            DrawCube((Vector3){i, -0.05f, j}, 1.0f, 0.1f, 1.0f, (Color){0, 153, 76, 50});
            DrawCubeWires((Vector3){i, -0.05f, j}, 1.0f, 0.1f, 1.0f, (Color){255, 255, 255, 50});
        }
    }
}