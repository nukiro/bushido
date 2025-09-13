#pragma once

#include <raylib.h>
#include <raymath.h>

#include "types.h"
#include "scene.h"
#include "config.h"

#define WALK 1
#define RUN 3

void update(Scene *scene, Camera3D *camera, float delta)
{
    Vector3 dir = {0.0f, 0.0f, 0.0f};
    if (IsKeyDown(KEY_W))
    {
        dir.x += 1.0f;
        dir.z += 1.0f;
    }
    if (IsKeyDown(KEY_S))
    {
        dir.x -= 1.0f;
        dir.z -= 1.0f;
    }
    if (IsKeyDown(KEY_A))
    {
        dir.x += 1.0f;
        dir.z -= 1.0f;
    }
    if (IsKeyDown(KEY_D))
    {
        dir.x -= 1.0f;
        dir.z += 1.0f;
    }

    // if all update conditions are true, then update
    if (dir.x != 0.0f || dir.z != 0.0f)
    {
        dir = Vector3Scale(Vector3Normalize(dir), RUN * delta);

        scene->nathan.position = Vector3Add(scene->nathan.position, dir);

        camera->position = Vector3Add(camera->position, dir);
        camera->target = Vector3Add(camera->target, dir);
    }
}