#include "render/rutils.h"

#include "types.h"
#include "common.h"
#include "render/rconfig.h"

void axis(const Volume *v)
{
    Vector3 from = {v->position.x, v->box.y, v->position.z};
    DrawLine3D(from, Vector3Add(from, X_AXIS), RENDER_COLOR_RED);
    DrawLine3D(from, Vector3Add(from, Y_AXIS), RENDER_COLOR_GREEN);
    DrawLine3D(from, Vector3Add(from, Z_AXIS), RENDER_COLOR_BLUE);
}