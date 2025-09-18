#pragma once

typedef int status;

enum
{
    STATUS_OK = 1,
    STATUS_ERR_ALLOC = -1001,
    STATUS_ERR_FILE_NOT_OPEN = -1002,
};

const char *status_str(status status);
