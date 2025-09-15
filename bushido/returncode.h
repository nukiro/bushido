#pragma once

typedef int rc;

typedef enum
{
    RC_OK = 0,
    RC_FILE_NOT_OPEN = 1,
    RC_MAP_HEADER_NOT_FOUND = 2,
    RC_MAP_CELLS_NOT_FOUND = 3,
    RC_MALLOC = 4,
    RC__COUNT
} rc_t;

static const char *const RC_MSG[RC__COUNT] = {
    [RC_OK] = "ok",
    [RC_FILE_NOT_OPEN] = "file not open",
    [RC_MAP_HEADER_NOT_FOUND] = "when loading the map, header not found",
    [RC_MAP_CELLS_NOT_FOUND] = "when loading the map, cells not found",
    [RC_MALLOC] = "when allocating memory",
};

_Static_assert(RC__COUNT == (int)(sizeof RC_MSG / sizeof RC_MSG[0]),
               "RC_MSG out of sync with rc_t");

const char *rc_str(rc rc)
{
    if (rc >= 0 && rc < RC__COUNT && RC_MSG[rc])
        return RC_MSG[rc];

    return "unknown error";
}