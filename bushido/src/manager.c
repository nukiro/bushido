#include "manager.h"

#include <stdio.h>

#include "debug.h"
#include "config.h"
#include "scene.h"
#include "fov.h"
#include "hero.h"

status manager_init(Manager *m)
{
    log_info("manager initializating...");
    // init window with config properties
    m->window = (Window){GAME_WINDOW_TITLE, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT};

    // init scene navigation
    snprintf(m->navigation.current, 6, "%s", GAME_NAVIGATION_SCENE_INIT);
    snprintf(m->navigation.previous, 6, "%s", GAME_NAVIGATION_SCENE_NULL);
    DBG("navigation scene init: %s", GAME_NAVIGATION_SCENE_INIT);

    // init hero as it is required in the scene and in the view camera
    m->hero = (Hero){0};
    hero_init(&m->hero);

    // allocate scene
    status st = scene_allocate(NULL, &m->scene, GAME_NAVIGATION_SCENE_INIT);
    if (!st)
    {
        return st;
    }

    // init view
    m->fov = (FieldOfVision){0};
    fov_init(&m->fov, &m->hero.volume);

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
    Manager m = {0};
    bool status = manager_init(&m);

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