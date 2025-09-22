#pragma once

#include <stddef.h>

struct Vector3;
#define X_AXIS (Vector3){1.0f, 0.0f, 0.0f}
#define Y_AXIS (Vector3){0.0f, 1.0f, 0.0f}
#define Z_AXIS (Vector3){0.0f, 0.0f, 1.0f}

enum
{
    STATUS_OK = 1,
    STATUS_ERR_ALLOC = -1001,
    STATUS_ERR_FILE_NOT_OPEN = -1002,
}; // return status codes

typedef void *(*alloc_fn)(size_t); // allocator signature