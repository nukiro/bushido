#pragma once

struct Scene;
#include "fov.h"
#include "hero.h"
#include "status.h"

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
    struct Scene *scene;
    FieldOfVision fov;
    Hero hero;

} Manager;

status manager_init(Manager *m);
void manager_close(Manager *m);