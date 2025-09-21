#pragma once

#include <stdio.h>
#include <raylib.h>

#include "debug.h"
#include "config.h"
#include "scene.h"
#include "view.h"
#include "hero.h"
#include "game.h"

typedef struct Navigation
{
    char current[6];
    char previous[6];
} Navigation;

typedef struct Window
{
    const char *title;
    int width;
    int height;
} Window;

typedef struct Manager
{
    Window window;
    Navigation navigation;
    Scene *scene;
    FieldOfVision fov;
    Hero hero;

} Manager;

status manager_init(Manager *manager, const Game *game);
void manager_close(Manager *manager);