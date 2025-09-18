#pragma once

#include "logger.h"

#ifdef DEBUG
#define DBG(...) log_debug(__VA_ARGS__)
#else
#define DBG(...) ((void)0)
#endif