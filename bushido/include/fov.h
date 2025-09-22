#pragma once

#include <raylib.h>

struct Volume;
struct FieldOfVision;

void fov_init(struct FieldOfVision *fov, const struct Volume *hero);