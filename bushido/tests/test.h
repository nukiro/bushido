#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef struct Test
{
    bool result;
    int failures;
    int total;
} Test;

void assert(Test *test, bool check, const char *msg)
{
    // increase total test counter
    ++test->total;

    // return if check is true, meaning test is valid
    if (check)
        return;

    printf("failed: %s\n", msg);

    // increase failures counter
    ++test->failures;
    // set it as false
    // no matter how many checks will executed within the test
    // if one fails, the test fails.
    test->result = false;
}
