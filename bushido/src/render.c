#include "render.h"

#define DEV_TOOL_FONT_SIZE 10
#define DEV_TOOL_MARGIN_X 5
#define DEV_TOOL_MARGIN_Y 5
#define DEV_TOOL_SEPARATOR 5

static int dev_position_y(int n)
{
    return DEV_TOOL_MARGIN_Y + ((DEV_TOOL_FONT_SIZE + DEV_TOOL_SEPARATOR) * n);
}

static const char *format_text(char buf[16], const char *s)
{
    if (!s)
        s = "No key!";

    snprintf(buf, 16, "%-15.15s", s);

    return buf;
}

static void dev_tool(Game *g, Manager *m)
{
    char buf[16];
    DrawText(TextFormat("%s%s", format_text(buf, "tag"), g->tag), DEV_TOOL_MARGIN_X, dev_position_y(0), DEV_TOOL_FONT_SIZE, LIME);
    DrawText(TextFormat("%s%dx%d", format_text(buf, "window"), m->window.width, m->window.height), DEV_TOOL_MARGIN_X, dev_position_y(1), DEV_TOOL_FONT_SIZE, LIME);
}

void render(Game *g, Manager *m)
{
    BeginDrawing();
    ClearBackground(RENDER_COLOR_BACKGROUND);

#ifdef DEBUG
    dev_tool(g, m);
#endif

    EndDrawing();
}