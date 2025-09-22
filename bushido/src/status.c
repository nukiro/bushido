#include "status.h"
#include "common.h"

const char *status_str(int status)
{
    if (status > 0)
        return "unknown status value";

    switch (status)
    {
    case STATUS_OK:
        return "ok";
    case STATUS_ERR_ALLOC:
        return "allocating memory";
    case STATUS_ERR_FILE_NOT_OPEN:
        return "opening file";
    default:
        return "unknown error";
    }
}
