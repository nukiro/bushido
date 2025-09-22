#include "render/rdev.h"

#include <raylib.h>
#include <stdio.h>

#include "types.h"
#include "render/rconfig.h"

static int dev_position_y(int n)
{
    return RENDER_DEV_INSIGHT_MARGIN_Y + ((RENDER_DEV_INSIGHT_FONT_SIZE + RENDER_DEV_INSIGHT_SEPARATOR) * n);
}

static const char *format_text(char buf[RENDER_DEV_TABLE_COLUMN_NAME], const char *s)
{
    if (!s)
        s = "< NO-KEY >";

    snprintf(buf, RENDER_DEV_TABLE_COLUMN_NAME, RENDER_DEV_TABLE_COLUMN_VALUE, s);

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

void render_dev_insight(const Manager *m)
{
    char buf[RENDER_DEV_TABLE_COLUMN_NAME];
    DrawText(TextFormat("%s%dx%d", format_text(buf, "window"), m->window.width, m->window.height), RENDER_DEV_INSIGHT_MARGIN_X, dev_position_y(0), RENDER_DEV_INSIGHT_FONT_SIZE, LIME);
}

void render_dev_graphics()
{
    origin();
}