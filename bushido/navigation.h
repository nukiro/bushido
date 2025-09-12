#include "types.h"

#pragma once

#define NAVIGATION_OUT -1
#define NAVIGATION_FREE 0
#define NAVIGATION_OBSTACLE 1

void navigation_init(NavigationScene *scene)
{
    scene->navigation[2][2] = NAVIGATION_OBSTACLE;
}