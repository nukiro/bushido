#include "render.h"

void render(const Game *g, Manager *m)
{
    BeginDrawing();
    ClearBackground(RENDER_COLOR_BACKGROUND);

    BeginMode3D(m->fov.camera);

    render_hero(&m->hero);

#ifdef DEBUG
    dev_graphics(m);
#endif

    EndMode3D();

#ifdef DEBUG
    dev_insight(g, m);
#endif

    EndDrawing();
}