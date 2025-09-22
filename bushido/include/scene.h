#pragma once

#include "types.h"
#include "status.h"

typedef struct Scene
{
    char id[6];
} Scene;

status scene_allocate(alloc_fn af, Scene **scene, const char *id);
void scene_deallocate(Scene **scene);