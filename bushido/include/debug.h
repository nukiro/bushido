#pragma once

#include "logger.h"

#ifdef DEBUG
#define DBG(...) log_debug(__VA_ARGS__)
#else
#define DBG(...) ((void)0)
#endif

struct Configuration;
int debug_init(struct Configuration *c);