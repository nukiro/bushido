#include "render.h"

#define RENDER_COLOR_BACKGROUND (Color){25, 25, 25, 1}

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
    dev_insights(g, m);
#endif

    EndDrawing();
}