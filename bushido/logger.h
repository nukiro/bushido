#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "returncode.h"

#define LOG_INFO "INFO"
#define LOG_ERROR "ERROR"

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

rc log_message(const char *category, const char *fmt, va_list ap)
{
    rc rc = RC_OK;
    if (!s_fp)
    {
        rc = RC_FILE_NOT_OPEN;
        fprintf(stderr, "log_message: %s\n", rc_str(rc));
        return rc;
    }

    char when[32];
    int msec = 0;
    make_timestamp(when, &msec);

    fprintf(s_fp, "%s.%03d [%s] ", when, msec, category);
    vfprintf(s_fp, fmt, ap);

    fputc('\n', s_fp);

#ifdef DEBUG
    fflush(s_fp);
#endif
    return rc;
}

rc log_info(const char *fmt, ...)
{
    rc rc;
    va_list ap;
    va_start(ap, fmt);
    rc = log_message(LOG_INFO, fmt, ap);
    va_end(ap);
    return rc;
}

rc log_error(const char *fmt, ...)
{
    rc rc;
    va_list ap;
    va_start(ap, fmt);
    rc = log_message(LOG_ERROR, fmt, ap);
    va_end(ap);
    return rc;
}

rc log_open(const char *path)
{
    rc rc = RC_OK;

    // already open
    if (s_fp)
        return rc;

    s_fp = fopen(path, "w");
    if (!s_fp)
    {
        rc = RC_FILE_NOT_OPEN;
        fprintf(stderr, "log_open: %s\n", rc_str(rc));
        return rc;
    }

    log_info("initializing...");
    return rc;
}

void log_close(void)
{
    log_info("all done!");

    // close logger pointer, do not log anything else
    if (s_fp)
    {
        // flush once last time before closing
        fflush(s_fp);
        fclose(s_fp);
        s_fp = NULL;
    }
}
