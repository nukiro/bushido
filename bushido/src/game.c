#include "game.h"

status game_init(Game *g)
{
    log_info("game initializing...");
    g->name = GAME_TITLE;

    DBG("game init");
    return STATUS_OK;
}

void game_close()
{
    log_info("all done!");
    DBG("game close");
}

#ifdef TEST

#include "assertions.h"

void it_should_init_close_game(Test *t)
{
    Game g = {0};

    bool status = game_init(&g);

    assert(t, status == 1, "game_init() should return ok when the game is initialized");
    assert(t, g.name != NULL, "game_init() should set name");

    game_close();
}

void test_game(void)
{
    Test t = {"Game", true, 0, 0};

    it_should_init_close_game(&t);

    result(t);
}

#endif