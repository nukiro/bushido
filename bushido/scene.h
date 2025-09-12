#include <raylib.h>

#include "types.h"
#include "navigation.h"
#include "nathan.h"

#pragma once

NavigationScene scene_init()
{
    NavigationScene scene = {0};
    nathan_init(&scene, 0, 0);
    navigation_init(&scene);
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

void scene_navigation_render(NavigationScene scene)
{
    for (int x = 0; x < NAVIGATION_X; x++)
    {
        for (int z = 0; z < NAVIGATION_Z; z++)
        {
            switch (navigation_at(scene, x, z))
            {
            case 1:
                _scene_render_obstacle(x, z);
                break;
            }

            _scene_render_ground(x, z);
        }
    }
}