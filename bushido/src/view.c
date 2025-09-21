#include "view.h"

static Vector3 target(const Hero *h)
{
    return (Vector3){h->volume.position.x, h->volume.box.y / 2, h->volume.position.z};
}

static Vector3 position(const Vector3 *t, Position p)
{
    Vector3 c;
    switch (p)
    {
    case Aerial:
        c = VIEW_POSITION_AERIAL;
        break;
    case Ground:
        c = VIEW_POSITION_GROUND;
        break;
    default:
        c = VIEW_POSITION_DEFAULT;
        break;
    }
    return Vector3Add(*t, c);
}

void view_init(View *c, const Hero *h)
{
    // use in positiion method to get camera Vector3 position
    c->position = GAME_VIEW_POSITION;

    Vector3 t = target(h);

    c->camera.position = position(&t, c->position);
    c->camera.target = t;
    c->camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    c->camera.fovy = ZOOM;
    c->camera.projection = CAMERA_ORTHOGRAPHIC;

    DBG("view init");
}