#pragma once

#include <raylib.h>
#include <raymath.h>

#include "types.h"
#include "logger.h"

#define BODY (Vector3){0.5f, 2.0f, 0.5f}
#define X_AXIS (Vector3){2.0f, 0.0f, 0.0f}
#define Z_AXIS (Vector3){0.0f, 0.0f, 2.0f}

void nathan_init(Scene *scene, size_t x, size_t z)
{
    Nathan n = {0};
    n.position = (Vector3){(float)x, 0.0f, (float)z};
    n.body = BODY;
    scene->nathan = n;
    log_info("init nathan at: x=%zu z=%zu", x, z);
}

void nathan_render(Nathan nathan)
{
    DrawCapsuleWires(nathan.position, Vector3Add(nathan.position, (Vector3){0.0f, nathan.body.y, 0.0f}), nathan.body.x - 0.1, 8, 8, PURPLE);
#ifdef DEBUG
    DrawCapsuleWires(nathan.position, Vector3Add(nathan.position, (Vector3){0.0f, nathan.body.y, 0.0f}), nathan.body.x, 8, 8, (Color){255, 255, 255, 100});
#endif

#ifdef DEBUG
    Vector3 from = Vector3Add(nathan.position, (Vector3){0.0f, nathan.body.y / 2, 0.0f});
    DrawLine3D(from, Vector3Add(from, X_AXIS), RED);
    DrawLine3D(from, Vector3Add(from, Z_AXIS), RED);
#endif
}