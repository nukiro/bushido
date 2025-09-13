#pragma once

#include "types.h"

#define MAP_NAVIGATION_OUT -1
#define MAP_NAVIGATION_FREE 0
#define MAP_NAVIGATION_OBSTACLE 1
#define MAP_NAVIGATION_HALF_OBSTACLE 2

void map_init(Scene *scene)
{
    scene->navigation[2][2] = MAP_NAVIGATION_OBSTACLE;
}

int map_at(Scene scene, int x, int z)
{
    if (x < 0 || x >= NAVIGATION_X)
    {
        return MAP_NAVIGATION_OUT;
    }

    if (z < 0 || z >= NAVIGATION_Z)
    {
        return NAVIGATION_Z;
    }

    return scene.navigation[x][z];
}

bool map_is_free_at(Scene scene, int x, int z)
{

    if (map_at(scene, x, z) == MAP_NAVIGATION_FREE)
    {
        return true;
    }

    return false;
}