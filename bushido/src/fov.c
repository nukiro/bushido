#include "fov.h"

#include <raymath.h>

#include "config.h"
#include "types.h"
#include "debug.h"

#define VIEW_POSITION_AERIAL(x) (Vector3){-0.001f, x, -0.001f}
#define VIEW_POSITION_GROUND(x) \
    (Vector3) { -1 * x, 0, -1 * x }
#define VIEW_POSITION_DEFAULT(x) \
    (Vector3) { -1 * x, x, -1 * x }

static Vector3 target(const Volume *v)
{
    return (Vector3){v->position.x, v->box.y / 2, v->position.z};
}

static Vector3 position(const Vector3 *t, View p, float z)
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

void fov_init(FieldOfVision *fov, const Volume *v, const Configuration *c)
{
    // use in position method to get camera Vector3 position
    fov->view = c->fov_view;

    Vector3 t = target(v);

    fov->camera.position = position(&t, fov->view, c->fov_zoom);
    fov->camera.target = t;
    fov->camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    fov->camera.fovy = c->fov_zoom;
    fov->camera.projection = CAMERA_ORTHOGRAPHIC;

    DBG("view init");
}