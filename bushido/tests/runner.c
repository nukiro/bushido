#include <stdio.h>

// register all for registration methods
#ifdef TEST

#endif

int main(void)
{
#ifdef TEST
    // run all tests
#endif
#ifndef TEST
    printf("TEST flag not defined.\n");
#endif
}