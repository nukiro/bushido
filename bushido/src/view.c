#include "view.h"

#define VIEW_POSITION_AERIAL(x) (Vector3){-0.001f, x, -0.001f}
#define VIEW_POSITION_GROUND(x) \
    (Vector3) { -1 * x, 0, -1 * x }
#define VIEW_POSITION_DEFAULT(x) \
    (Vector3) { -1 * x, x, -1 * x }

static Vector3 target(const Volume *v)
{
    return (Vector3){v->position.x, v->box.y / 2, v->position.z};
}

static Vector3 position(const Vector3 *t, CameraPosition p, float z)
{
    Vector3 c;
    switch (p)
    {
    case Aerial:
        c = VIEW_POSITION_AERIAL(z);
        break;
    case Ground:
        c = VIEW_POSITION_GROUND(z);
        break;
    default:
        c = VIEW_POSITION_DEFAULT(z);
        break;
    }
    return Vector3Add(*t, c);
}

void view_init(View *c, const Volume *v)
{
    // use in positiion method to get camera Vector3 position
    c->position = GAME_VIEW_POSITION;

    Vector3 t = target(v);

    c->camera.position = position(&t, c->position, GAME_VIEW_ZOOM);
    c->camera.target = t;
    c->camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    c->camera.fovy = GAME_VIEW_ZOOM;
    c->camera.projection = CAMERA_ORTHOGRAPHIC;

    DBG("view init");
}