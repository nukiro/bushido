#include <stdio.h>

// register all for registration methods
#ifdef TEST
extern void test_game(void);
extern void test_manager(void);
extern void test_scene(void);
#endif

int main(void)
{
#ifdef TEST
    // run all tests
    test_game();
    test_manager();
    test_scene();
#endif
#ifndef TEST
    printf("TEST flag not defined.\n");
#endif
}