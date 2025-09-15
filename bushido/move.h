#pragma once

#include <raylib.h>

void move_check_map_boundaries(Vector3 pos, Vector3 *dir, int max_x, int max_z)
{
    if (pos.x < 0 || pos.x > max_x)
        dir->x = 0;

    if (pos.z < 0 || pos.z > max_z)
        dir->z = 0;
}