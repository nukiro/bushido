#pragma once

#include <raylib.h>

struct Volume;
struct FieldOfVision;
struct Configuration;

void fov_init(struct FieldOfVision *fov, const struct Volume *hero, const struct Configuration *config);