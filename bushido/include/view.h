#pragma once

#include <raylib.h>
#include <raymath.h>

#include "config.h"
#include "debug.h"
#include "volume.h"

#define ZOOM 10.0f

#define VIEW_POSITION_AERIAL (Vector3){-0.001f, ZOOM, -0.001f}
#define VIEW_POSITION_GROUND \
    (Vector3) { -1 * ZOOM, 0, -1 * ZOOM }
#define VIEW_POSITION_DEFAULT \
    (Vector3) { -1 * ZOOM, ZOOM, -1 * ZOOM }

typedef enum
{
    Default,
    Aerial,
    Ground,
} Position;

typedef struct View
{
    Position position;
    Camera camera;
} View;

void view_init(View *view, const Volume *volume);