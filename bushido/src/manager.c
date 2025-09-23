#include "manager.h"

#include <stdio.h>

#include "debug.h"
#include "config.h"
#include "types.h"
#include "common.h"
#include "hero.h"
#include "scene.h"
#include "fov.h"

int manager_init(Manager *m, const Configuration *c)
{
    log_info("manager initializating...");
    // init window with config properties
    m->window = (Window){GAME_WINDOW_TITLE, c->window_width, c->window_height};

    // init scene navigation
    snprintf(m->navigation.current, 6, "%s", c->navigation_scene_init);
    snprintf(m->navigation.previous, 6, "%s", GAME_NAVIGATION_SCENE_NULL);
    DBG("navigation scene init: %s", c->navigation_scene_init);

    // init hero as it is required in the scene and in the view camera
    m->hero = (Hero){0};
    hero_init(&m->hero);

    // allocate scene
    int st = scene_allocate(NULL, &m->scene, c->navigation_scene_init);
    if (!st)
    {
        return st;
    }

    // init view
    m->fov = (FieldOfVision){0};
    fov_init(&m->fov, &m->hero.volume, c);

    DBG("manager init");
    return STATUS_OK;
}

void manager_close(Manager *m)
{
    if (m)
    {
        scene_deallocate(&m->scene);
    }
    DBG("manager closed");
}

#ifdef TEST

#include "assertions.h"

#include "string.h"

void it_should_init_close_manager(Test *t)
{
    Game g = {0};
    Manager m = {0};
    bool status = manager_init(&m, &g);

    assert(t, status == 1, "manager_init() should return ok when the manager is initialized");
    assert(t, strcmp(m.navigation.current, GAME_NAVIGATION_SCENE_INIT) == 0, "manager_init() should initialize the current navigation");
    assert(t, strcmp(m.navigation.previous, GAME_NAVIGATION_SCENE_NULL) == 0, "manager_init() should initialize the previous navigation");
    assert(t, m.scene != NULL, "manager_init() should set scene manager pointer after its allocation");

    manager_close(&m);
}

void test_manager(void)
{
    Test t = {"Manager", true, 0, 0};

    it_should_init_close_manager(&t);

    result(t);
}
#endif