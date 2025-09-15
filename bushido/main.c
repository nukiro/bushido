#include "window.h"
#include "update.h"
#include "render.h"
#include "logger.h"
#include "config.h"
#include "game.h"

int main(void)
{

    if (log_open(LOG_FILE) != RC_OK)
        return 1;

    Game game = game_init();

    window_init(game);

    window_loop(&game, update, render);

    window_close();

    game_close_scene(&game);

    log_close();

    return 0;
}