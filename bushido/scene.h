#include <raylib.h>

#include "types.h"
#include "map.h"
#include "nathan.h"
#include "logger.h"

#pragma once

#define SCENE_FACING_NORTH 0
#define SCENE_FACING_EAST 1
#define SCENE_FACING_SOUTH 2
#define SCENE_FACING_WEST 3

Scene scene_init(Game game, int facing)
{
    Scene scene = {0};
    snprintf(scene.code, sizeof scene.code, "%s", game.code);
    snprintf(scene.from, sizeof scene.from, "%s", game.from);
    log_info("init scene: %s from %s", scene.code, scene.from);
    scene.map = (Map){0};
    scene.n_doors = 0;
    scene.to = 0;

    size_t la = strlen(game.path), lb = strlen(game.code);
    char *buf = malloc(la + lb + 1);
    if (buf)
    {

        memcpy(buf, game.path, la);
        memcpy(buf + la, game.code, lb);
        buf[la + lb] = '\0';

        scene.path = buf; // OK: char* -> const char* (adds const)
    }
    else
        log_error("%s => scene init path", rc_str(RC_MALLOC));

    log_info("scene path => %s", scene.path);

    scene.facing = SCENE_FACING_NORTH;

    if (facing >= SCENE_FACING_NORTH && facing <= SCENE_FACING_WEST)
        scene.facing = facing;

#ifdef DEBUG
    if (facing == -1)
    {
        scene.facing = -1;
    }
#endif
    log_info("scene facing: %d", scene.facing);

    map_init(&scene);

    scene.is_ready = true;
    scene.is_done = false;

    return scene;
}

void scene_free(Scene *scene)
{
    if (!scene)
        return;
    // deallocate map
    map_free(&scene->map);
    // deallocate doors
    free(scene->doors);
    scene->doors = NULL;
    scene->n_doors = 0;
    // deallocate path
    free((void *)scene->path);
    scene->path = NULL;
    scene->is_ready = false;
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

static void scene_render_door(float x, float z)
{
    // DrawCube((Vector3){x, 1.25f, z + 0.55f}, 0.9f, 2.5f, 0.1f, (Color){102, 0, 0, 255});
    // DrawCubeWires((Vector3){x, 1.25f, z + 0.55f}, 0.9f, 2.5f, 0.1f, (Color){255, 255, 255, 100});
#ifdef DEBUG
    DrawCubeWires((Vector3){x, 0.5f, z}, 1.0f, 1.0f, 1.0f, (Color){255, 255, 255, 150});
#endif
}

void scene_map_render(Map map)
{
    for (int x = 0; x < map.x; x++)
    {
        for (int z = 0; z < map.z; z++)
        {
            switch (map_at(map, x, z))
            {
            case MAP_NAVIGATION_OBSTACLE:
                scene_render_obstacle(x, z);
                break;
            case 'A' ... 'Z':
                scene_render_door(x, z);
                break;
                break;
            }

            scene_render_ground(x, z);
        }
    }
}

void scene_action(Scene *scene)
{
    Scene s = *scene;
    size_t x = 0, z = 0;
    nathan_action(scene->nathan, &x, &z);
    int a = map_at(s.map, x, z);
#ifdef DEBUG
    log_info("at: x=%zu z=%zu | action: %c", x, z, a);
#endif

    switch (a)
    {
    case 'A' ... 'Z':
        scene->to = a - 65;
        scene->is_done = true;
        return;
    }
}

char *scene_destination(Scene *scene)
{
    return scene->doors[scene->to];
}