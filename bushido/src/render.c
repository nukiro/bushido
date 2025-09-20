#include "render.h"

#define RENDER_COLOR_BACKGROUND (Color){25, 25, 25, 1}

void render(const Game *g, Manager *m)
{
    BeginDrawing();
    ClearBackground(RENDER_COLOR_BACKGROUND);

#ifdef DEBUG
    dev(g, m);
#endif

    EndDrawing();
}