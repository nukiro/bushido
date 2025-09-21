#pragma once

#include <raylib.h>
#include <raymath.h>

#include "volume.h"
#include "render/rconfig.h"

#define X_AXIS (Vector3){1.0f, 0.0f, 0.0f}
#define Y_AXIS (Vector3){0.0f, 1.0f, 0.0f}
#define Z_AXIS (Vector3){0.0f, 0.0f, 1.0f}

void axis(const Volume *volume);