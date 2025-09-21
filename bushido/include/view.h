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
} View;

typedef struct FieldOfVision
{
    View view;
    Camera camera;
} FieldOfVision;

void view_init(FieldOfVision *fov, const Volume *volume);