#include "window.h"
#include "update.h"
#include "render.h"

int main(void)
{

    window_init();

    window_loop(update, render);

    window_close();

    return 0;
}