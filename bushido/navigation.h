#include "types.h"

#pragma once

#define NAVIGATION_OUT -1
#define NAVIGATION_FREE 0
#define NAVIGATION_OBSTACLE 1

void navigation_init(NavigationScene *scene)
{
    scene->navigation[2][2] = NAVIGATION_OBSTACLE;
}

int navigation_at(NavigationScene scene, int x, int z)
{
    if (x < 0 || x >= NAVIGATION_X)
    {
        return NAVIGATION_OUT;
    }

    if (z < 0 || z >= NAVIGATION_Z)
    {
        return NAVIGATION_OUT;
    }

    return scene.navigation[x][z];
}

bool navigation_at_free(NavigationScene scene, int x, int z)
{

    if (navigation_at(scene, x, z) == NAVIGATION_FREE)
    {
        return true;
    }

    return false;
}