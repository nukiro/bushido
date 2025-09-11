#include <raylib.h>

#include "nathan.h"

#pragma once

typedef struct Scene
{
    Nathan nathan;
} Scene;

Scene scene_init()
{
    Scene scene = {0};
    return scene;
}
