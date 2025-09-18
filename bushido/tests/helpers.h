#pragma once

#include <stddef.h>

static void *fail_malloc(size_t n)
{
    (void)n;
    return NULL;
}