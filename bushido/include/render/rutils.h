#pragma once

#include <raylib.h>
#include <raymath.h>

#include "volume.h"

#define X_AXIS (Vector3){1.0f, 0.0f, 0.0f}
#define X_COLOR (Color){255, 0, 0, 100}
#define Y_AXIS (Vector3){0.0f, 1.0f, 0.0f}
#define Y_COLOR (Color){0, 255, 0, 100}
#define Z_AXIS (Vector3){0.0f, 0.0f, 1.0f}
#define Z_COLOR (Color){0, 0, 255, 100}

void axis(const Volume *volume);