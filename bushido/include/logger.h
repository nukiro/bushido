#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "status.h"

void log_debug(const char *fmt, ...);
void log_info(const char *fmt, ...);
void log_error(const char *fmt, ...);
status log_open(const char *path);
void log_close(void);
