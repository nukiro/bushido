#include "scene.h"

status scene_allocate(alloc_fn af, Scene **scene, const char *id)
{
    *scene = NULL;

    if (!af)
        af = malloc;

    Scene *s = af(sizeof *s);
    if (!s)
    {
        log_error("allocating scene %s", id);
        return STATUS_ERR_ALLOC;
    }

    snprintf(s->id, 6, "%s", id);

    *scene = s;

    DBG("scene allocated: %s", id);
    return STATUS_OK;
}

void scene_deallocate(Scene **scene)
{
    const char *id = (*scene)->id;
    if (!scene || !*scene)
        return;

    free(*scene);
    *scene = NULL;
    DBG("scene deallocated: %s", id);
}

#ifdef TEST

#include "assertions.h"
#include "helpers.h"

#include "string.h"

void it_should_allocate_scene(Test *t)
{
    Scene *s;
    const char *id = "12345";

    bool status = scene_allocate(NULL, &s, id);

    assert(t, status == 1, "scene_allocate() should return status ok when the scene is allocated");
    assert(t, strcmp(s->id, "12345") == 0, "scene_allocate() should initialize id");
    assert(t, s != NULL, "scene_allocate() should set the pointer into scene pointer");

    scene_deallocate(&s);
}

void it_should_return_error_when_not_allocate_scene(Test *t)
{
    Scene *s;
    const char *id = "12345";

    bool status = scene_allocate(fail_malloc, &s, id);

    assert(t, status = -1001, "scene_allocate() should return error when the scene is not allocated");
    assert(t, s == NULL, "scene_allocate() should not set scene pointer");

    scene_deallocate(&s);
}

void it_should_deallocate_scene(Test *t)
{
    Scene *s;
    const char *id = "12345";

    scene_allocate(NULL, &s, id);
    scene_deallocate(&s);

    assert(t, s == NULL, "scene_deallocate() should set as NULL variable that points to scene pointer");
}

void test_scene(void)
{
    Test t = {"Scene", true, 0, 0};

    it_should_allocate_scene(&t);
    it_should_return_error_when_not_allocate_scene(&t);
    it_should_deallocate_scene(&t);

    result(t);
}

#endif