#include "render/hero.h"

#include "types.h"

#include "render/utils.h"
#include "render/config.h"

static void body(const Volume *v)
{
    DrawCapsuleWires(v->position, Vector3Add(v->position, (Vector3){0.0f, v->box.y, 0.0f}), (v->box.x / 2), 8, 8, PURPLE);
}

static void box(const Volume *v)
{
    DrawCubeWires(Vector3Add(v->position, (Vector3){0.0f, v->box.y / 2, 0.0f}), v->box.x, v->box.y, v->box.z, RENDER_COLOR_DEBUG);
}

void render_hero(const Volume *v)
{
#ifdef DEBUG
    box(v);
    axis(v);
#endif
    body(v);
}