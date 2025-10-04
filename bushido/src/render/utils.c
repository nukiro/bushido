#include "render/utils.h"

#include "types.h"
#include "common.h"
#include "render/config.h"

void axis(const Volume *v)
{
    DrawLine3D(v->position, Vector3Add(v->position, X_AXIS), RENDER_COLOR_RED);
    DrawLine3D(v->position, Vector3Add(v->position, Y_AXIS), RENDER_COLOR_GREEN);
    DrawLine3D(v->position, Vector3Add(v->position, Z_AXIS), RENDER_COLOR_BLUE);
}