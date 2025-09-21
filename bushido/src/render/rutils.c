#include "render/rutils.h"

void axis(const Volume *v)
{
    // Vector3 from = Vector3Add(*v, (Vector3){0.0f, v->y / 2, 0.0f});
    Vector3 from = {v->position.x, v->box.y, v->position.z};
    DrawLine3D(from, Vector3Add(from, X_AXIS), X_COLOR);
    DrawLine3D(from, Vector3Add(from, Y_AXIS), Y_COLOR);
    DrawLine3D(from, Vector3Add(from, Z_AXIS), Z_COLOR);
}