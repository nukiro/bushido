#include "render.h"

#include "types.h"
#include "render/config.h"
#include "render/debug.h"
#include "render/hero.h"

#include <stdio.h>

void render(Manager *m)
{
    BeginDrawing();
    ClearBackground(RENDER_COLOR_BACKGROUND);

    BeginMode3D(m->fov.camera);

    render_hero(&m->hero.volume);

#ifdef DEBUG
    render_debug_graphics();
#endif

    EndMode3D();

#ifdef DEBUG
    render_debug_insight(m);
#endif

    EndDrawing();
}