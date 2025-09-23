#include "logger.h"
#include "config.h"
#include "game.h"
#include "manager.h"
#include "window.h"
#include "types.h"
#include "debug.h"

int main(void)
{
    Configuration config = {0};
#ifdef DEBUG
    if (!debug_init(&config))
    {
        return 1;
    }
#endif

    if (!log_init(GAME_LOG_FILE))
        return 1;

    Game game = {0};
    if (!game_init(&game))
        return 1;

    Manager manager = {0};
    if (!manager_init(&manager))
        return 1;

    window_init(&game, &manager);

    window_loop(&manager);

    window_close();

    game_close();

    log_close();

    return 0;
}