#include <raylib.h>

#include "types.h"
#include "map.h"
#include "nathan.h"

#pragma once

#define SCENE_FACING_NORTH 0
#define SCENE_FACING_EAST 1
#define SCENE_FACING_SOUTH 2
#define SCENE_FACING_WEST 3

Scene scene_init(int facing)
{
    Scene scene = {0};

    scene.facing = SCENE_FACING_NORTH;

    if (facing >= SCENE_FACING_NORTH && facing <= SCENE_FACING_WEST)
        scene.facing = facing;

#ifdef DEBUG
    if (facing == -1)
    {
        scene.facing = -1;
    }
#endif

    nathan_init(&scene, 0, 0);
    map_init(&scene);
    return scene;
}

static void scene_render_ground(float x, float z)
{
    DrawCube((Vector3){x, -0.05f, z}, 1.0f, 0.1f, 1.0f, (Color){0, 102, 51, 255});
    DrawCubeWires((Vector3){x, -0.05f, z}, 1.0f, 0.1f, 1.0f, (Color){255, 255, 255, 50});
}

static void scene_render_obstacle(float x, float z)
{
    DrawCube((Vector3){x, 0.5f, z}, 0.9f, 0.9f, 0.9f, (Color){102, 0, 0, 255});
    DrawCubeWires((Vector3){x, 0.5f, z}, 0.9f, 0.9f, 0.9f, (Color){255, 255, 255, 100});
#ifdef DEBUG
    DrawCubeWires((Vector3){x, 0.5f, z}, 1.0f, 1.0f, 1.0f, (Color){255, 255, 255, 150});
#endif
}

void scene_navigation_render(Scene scene)
{
    for (int x = 0; x < NAVIGATION_X; x++)
    {
        for (int z = 0; z < NAVIGATION_Z; z++)
        {
            switch (map_at(scene, x, z))
            {
            case 1:
                scene_render_obstacle(x, z);
                break;
            }

            scene_render_ground(x, z);
        }
    }
}