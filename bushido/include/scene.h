#pragma once

#include "common.h"

struct Scene;

int scene_allocate(alloc_fn af, struct Scene **scene, const char *id);
void scene_deallocate(struct Scene **scene);