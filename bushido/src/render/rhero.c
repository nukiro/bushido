#include "render/rhero.h"

static void body(const Hero *h)
{
    DrawCapsuleWires(h->volume.position, Vector3Add(h->volume.position, (Vector3){0.0f, h->volume.box.y, 0.0f}), (h->volume.box.x / 2), 8, 8, PURPLE);
}

static void box(const Hero *h)
{
    DrawCubeWires(Vector3Add(h->volume.position, (Vector3){0.0f, h->volume.box.y / 2, 0.0f}), h->volume.box.x, h->volume.box.y, h->volume.box.z, RENDER_COLOR_DEBUG);
}

void render_hero(const Hero *h)
{
#ifdef DEBUG
    box(h);
    axis(&h->volume);
#endif
    body(h);
}