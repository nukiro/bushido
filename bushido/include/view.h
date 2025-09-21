#pragma once

#include <raylib.h>
#include <raymath.h>

#include "config.h"
#include "debug.h"
#include "volume.h"

typedef enum
{
    Default,
    Aerial,
    Ground,
} CameraPosition;

typedef struct View
{
    CameraPosition position;
    Camera camera;
} View;

void view_init(View *view, const Volume *volume);