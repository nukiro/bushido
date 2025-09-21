#include "manager.h"

#define RESOLUTION_1080 1
#define RESOLUTION_1440 2
#define RESOLUTION_4K 3

static inline void resolution(int r, int *w, int *h)
{
    switch (r)
    {
    case RESOLUTION_1080:
        *w = 1920;
        *h = 1080;
        break;
    case RESOLUTION_1440:
        *w = 2560;
        *h = 1440;
        break;
    case RESOLUTION_4K:
        *w = 3840;
        *h = 2160;
        break;
    default:
        break;
    }
}

status manager_init(Manager *m, const Game *g)
{
    log_info("manager initializating...");
    // init window with default config values
    int w = GAME_WINDOW_WIDTH, h = GAME_WINDOW_HEIGHT;
    resolution(g->config.resolution, &w, &h);
    m->window = (Window){GAME_WINDOW_TITLE, w, h};

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
    view_init(&m->fov, &m->hero.volume);

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