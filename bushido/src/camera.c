#include "camera.h"

#define ZOOM 10.0f

static Vector3 target(const Hero *h)
{
    return (Vector3){h->position.x, h->box.y / 2, h->position.z};
}

static Vector3 position(const Vector3 *t)
{
    return Vector3Add(*t, (Vector3){-1 * ZOOM, ZOOM, -1 * ZOOM});
}

void camera_init(Camera3D *c, const Hero *h)
{
    Vector3 t = target(h);
    c->position = position(&t);
    c->target = t;
    c->up = (Vector3){0.0f, 1.0f, 0.0f};
    c->fovy = ZOOM;
    c->projection = CAMERA_ORTHOGRAPHIC;

    DBG("camera init");
}