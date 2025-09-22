#pragma once

#include <raylib.h>

struct Volume;

typedef enum
{
    Default,
    Aerial,
    Ground,
} View;

typedef struct FieldOfVision
{
    View view;
    Camera camera; // raylib Camera3D
} FieldOfVision;

void fov_init(FieldOfVision *fov, const struct Volume *volume);