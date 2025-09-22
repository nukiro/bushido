#pragma once

struct Vector3;
struct Volume;

#define X_AXIS (Vector3){1.0f, 0.0f, 0.0f}
#define Y_AXIS (Vector3){0.0f, 1.0f, 0.0f}
#define Z_AXIS (Vector3){0.0f, 0.0f, 1.0f}

void axis(const struct Volume *volume);