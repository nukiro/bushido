#include "render/debug.h"

#include <stdio.h>

#include "types.h"
#include "render/config.h"

#define RENDER_DEBUG_TEXT_BUFFER_SIZE 16

static int position_y(int n)
{
    return RENDER_DEBUG_INSIGHT_MARGIN_Y + ((RENDER_DEBUG_INSIGHT_FONT_SIZE + RENDER_DEBUG_INSIGHT_SEPARATOR) * n);
}

static const char *format_text(char buf[RENDER_DEBUG_TEXT_BUFFER_SIZE], const char *s)
{
    if (!s)
        s = "< NO-KEY >";

    snprintf(buf, RENDER_DEBUG_TEXT_BUFFER_SIZE, "%-15.15s", s);

    return buf;
}

static void origin()
{
    // full origin lines
    DrawLine3D((Vector3){-0.5f, 0.0f, -0.5f}, (Vector3){1.0f, 0.0f, -0.5f}, RENDER_COLOR_DEBUG);
    DrawLine3D((Vector3){-0.5f, 0.0f, -0.5f}, (Vector3){-0.5f, 0.0f, 1.0f}, RENDER_COLOR_DEBUG);
    // define first grid position
    DrawLine3D((Vector3){0.5f, 0.0f, -0.5f}, (Vector3){0.5f, 0.0f, 0.5f}, RENDER_COLOR_DEBUG);
    DrawLine3D((Vector3){-0.5f, 0.0f, 0.5f}, (Vector3){0.5f, 0.0f, 0.5f}, RENDER_COLOR_DEBUG);
}

void render_debug_insight(const Manager *m)
{
    char buf[RENDER_DEBUG_TEXT_BUFFER_SIZE]; // fifteen character string and null value
    DrawText(TextFormat("%s%d", format_text(buf, "FPS"), GetFPS()), RENDER_DEBUG_INSIGHT_MARGIN_X, position_y(0), RENDER_DEBUG_INSIGHT_FONT_SIZE, LIME);
    DrawText(TextFormat("%s%dx%d", format_text(buf, "WINDOW"), m->window.width, m->window.height), RENDER_DEBUG_INSIGHT_MARGIN_X, position_y(1), RENDER_DEBUG_INSIGHT_FONT_SIZE, LIME);
}

void render_debug_graphics()
{
    origin();
}