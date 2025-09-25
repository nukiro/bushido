#include "logger.h"
#include "config.h"
#include "game.h"
#include "manager.h"
#include "window.h"
#include "types.h"
#include "debug.h"
#include "utils.h"

int main(void)
{
    if (!was_executed_successfully(log_init()))
        return 1;

    Configuration config = {0};
    config_init(&config);
#ifdef DEBUG
    if (!was_executed_successfully(debug_init(&config)))
    {
        log_close();
        return 1;
    }
#endif

    Game game = {0};
    if (!game_init(&game))
    {
        log_close();
        return 1;
    }

    Manager manager = {0};
    if (!manager_init(&manager, &config))
    {
        game_close();
        log_close();
        return 1;
    }

    window_init(&game, &manager, &config);

    window_loop(&manager);

    window_close();

    game_close();

    log_close();

    return 0;
}