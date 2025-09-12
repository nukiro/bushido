#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

static FILE *s_fp = NULL;

static void make_timestamp(char out[32], int *msec_out)
{
    struct timespec ts;
    if (timespec_get(&ts, TIME_UTC) != TIME_UTC)
    {
        out[0] = '\0';
        *msec_out = 0;
        return;
    }

    time_t t = ts.tv_sec;
    struct tm *lt = localtime(&t);
    if (!lt)
    {
        out[0] = '\0';
        *msec_out = 0;
        return;
    }

    strftime(out, 32, "%Y-%m-%d %H:%M:%S", lt);
    *msec_out = (int)(ts.tv_nsec / 1000000L);
}

bool log_message(const char *fmt, ...)
{
    if (!s_fp)
    {
        perror("log file not opened");
        return false;
    }

    char when[32];
    int msec = 0;
    make_timestamp(when, &msec);

    fprintf(s_fp, "%s.%03d ", when, msec);

    va_list ap;
    va_start(ap, fmt);
    vfprintf(s_fp, fmt, ap);
    va_end(ap);

    fputc('\n', s_fp);

#ifdef DEBUG
    fflush(s_fp);
#endif
    return true;
}

bool log_open(const char *path)
{
    // already open
    if (s_fp)
        return true;

    s_fp = fopen(path, "w");
    if (!s_fp)
    {
        perror("failed opening log file");
        return false;
    }

    log_message("initializing game ...");
    return true;
}

void log_close(void)
{
    log_message("game closed");
    if (s_fp)
    {
        fflush(s_fp);
        fclose(s_fp);
        s_fp = NULL;
    }
}
