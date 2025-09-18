#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "status.h"
#include "logger.h"
#include "debug.h"

typedef struct Scene
{
    char id[6];
} Scene;

status scene_allocate(alloc_fn af, Scene **scene, const char *id);
void scene_deallocate(Scene **scene);