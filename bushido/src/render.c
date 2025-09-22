#include "render.h"

#include <raylib.h>

#include "game.h"
#include "manager.h"

#include "render/rconfig.h"
#include "render/rdev.h"
#include "render/rhero.h"

void render(const Game *g, Manager *m)
{
    BeginDrawing();
    ClearBackground(RENDER_COLOR_BACKGROUND);

    BeginMode3D(m->fov.camera);

    render_hero(&m->hero.volume);

#ifdef DEBUG
    render_dev_graphics();
#endif

    EndMode3D();

#ifdef DEBUG
    render_dev_insight(g, m);
#endif

    EndDrawing();
}