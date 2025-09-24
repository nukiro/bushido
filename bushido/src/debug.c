#include "debug.h"

#include <yaml.h>

#include "common.h"
#include "types.h"
#include "debug.h"
#include "config.h"

int debug_init(Configuration *c)
{
    DBG("debug mode on");

    FILE *file = fopen("debug.yaml", "r");
    // if we are in debug mode, but no debug configuration is set
    // just return OK as the default configuration is applied
    if (!file)
    {
        DBG("no debug configuration file, default configuration applied");
        return STATUS_OK;
    }

    fclose(file);

    return STATUS_OK;
}