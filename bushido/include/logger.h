#pragma once

void log_debug(const char *fmt, ...);
void log_info(const char *fmt, ...);
void log_error(const char *fmt, ...);
int log_open(const char *path);
void log_close(void);
