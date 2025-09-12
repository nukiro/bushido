#include <raylib.h>
#include <raymath.h>

#include "scene.h"
#include "types.h"

#pragma once

#define ZOOM 10.0f

Camera3D camera_init(NavigationScene *scene)
{
    Vector3 p = Vector3Add(scene->nathan.position, (Vector3){-1 * ZOOM, ZOOM, -1 * ZOOM});
    Vector3 t = Vector3Add(scene->nathan.position, (Vector3){0.0f, scene->nathan.body.y / 2, 0.0f});

    Camera3D camera = {0};
    camera.position = p;
    camera.target = t;
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = ZOOM;
    camera.projection = CAMERA_ORTHOGRAPHIC;

    return camera;
}