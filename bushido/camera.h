#include <raylib.h>
#include <raymath.h>

#include "scene.h"
#include "types.h"

#pragma once

#define ZOOM 10.0f
#define CAMERA_FACING_NORTH \
    (Vector3) { -1 * ZOOM, ZOOM, -1 * ZOOM }
#define CAMERA_FACING_SOUTH \
    (Vector3) { ZOOM, ZOOM, ZOOM }
#define CAMERA_FACING_WEST \
    (Vector3) { -1 * ZOOM, ZOOM, 1 * ZOOM }
#define CAMERA_FACING_EAST \
    (Vector3) { 1 * ZOOM, ZOOM, -1 * ZOOM }

Camera3D camera_init(Scene *scene)
{
    Vector3 p = {0};
    switch (scene->facing)
    {
    case SCENE_FACING_NORTH:
        p = Vector3Add(scene->nathan.position, CAMERA_FACING_NORTH);
        break;
    case SCENE_FACING_SOUTH:
        p = Vector3Add(scene->nathan.position, CAMERA_FACING_SOUTH);
        break;
    case SCENE_FACING_WEST:
        p = Vector3Add(scene->nathan.position, CAMERA_FACING_WEST);
        break;
    case SCENE_FACING_EAST:
        p = Vector3Add(scene->nathan.position, CAMERA_FACING_EAST);
        break;
    }

    Vector3 t = Vector3Add(scene->nathan.position, (Vector3){0.0f, scene->nathan.body.y / 2, 0.0f});

    Camera3D camera = {0};
    camera.position = p;
    camera.target = t;
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = ZOOM;
    camera.projection = CAMERA_ORTHOGRAPHIC;

    return camera;
}