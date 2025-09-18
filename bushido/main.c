#include "src/window.h"
#include "src/update.h"
#include "src/render.h"
#include "src/logger.h"
#include "src/config.h"
#include "src/game.h"

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