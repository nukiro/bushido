#include <raylib.h>

#pragma once

typedef struct Nathan
{
    Vector3 position;
    Vector3 body;
} Nathan;

#define NAVIGATION_X 5
#define NAVIGATION_Z 5

typedef struct NavigationScene
{
    Nathan nathan;
    int navigation[NAVIGATION_X][NAVIGATION_Z];
} NavigationScene;