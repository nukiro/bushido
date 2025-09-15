#include "window.h"
#include "update.h"
#include "render.h"
#include "logger.h"
#include "config.h"

int main(void)
{

    if (log_open(LOG_FILE) != RC_OK)
        return 1;

    window_init();

    window_loop(update, render);

    window_close();

    log_close();

    return 0;
}