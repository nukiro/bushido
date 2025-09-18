#include "logger.h"

#define LOG_DEBUG "DEBUG"
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

static void log_message(const char *category, const char *fmt, va_list ap)
{
#ifdef TEST
    return;
#endif

    if (!s_fp)
    {
        fprintf(stderr, "[ERROR] {log_message}: %s\n", status_str(STATUS_ERR_FILE_NOT_OPEN));
        return;
    }

    char when[32];
    int msec = 0;
    make_timestamp(when, &msec);

    fprintf(s_fp, "%s.%03d [%s] ", when, msec, category);
    vfprintf(s_fp, fmt, ap);

    fputc('\n', s_fp);

#ifdef DEBUG
    // when debug flush messages instantaneously
    fflush(s_fp);
#endif
}

void log_debug(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    log_message(LOG_DEBUG, fmt, ap);
    va_end(ap);
}

void log_info(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    log_message(LOG_INFO, fmt, ap);
    va_end(ap);
}

void log_error(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    log_message(LOG_ERROR, fmt, ap);
    va_end(ap);
}

status log_open(const char *path)
{
#ifdef TEST
    return STATUS_OK;
#endif

    if (!path)
    {
        fprintf(stderr, "[ERROR] {log_open}: path is required\n");
        return STATUS_ERR_FILE_NOT_OPEN;
    }
    // already open
    if (s_fp)
        return STATUS_OK;

    s_fp = fopen(path, "w");
    if (!s_fp)
    {
        fprintf(stderr, "[ERROR] {log_open}: %s\n", status_str(STATUS_ERR_FILE_NOT_OPEN));
        return STATUS_ERR_FILE_NOT_OPEN;
    }
    return STATUS_OK;
}

void log_close(void)
{
#ifdef TEST
    return;
#endif
    // close logger pointer, do not log anything else
    if (s_fp)
    {
        // flush once last time before closing
        fflush(s_fp);
        fclose(s_fp);
        s_fp = NULL;
    }
}
