#pragma once

#include <stdio.h>

#include "config.h"
#include "scene.h"
#include "debug.h"

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

} Manager;

status manager_init(Manager *m);
void manager_close(Manager *m);