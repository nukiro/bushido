#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef struct Test
{
    const char *id;
    bool result;
    int failures;
    int assertions;
} Test;

static void result(const Test test)
{
    if (test.assertions == 0)
    {
        printf("no %s tests\n", test.id);
        printf("-----\n");
        return;
    }

    if (test.result)
        printf("\x1b[1;32mall %s tests (%d assertions) run successfully\x1b[0m\n", test.id, test.assertions);
    else
        printf("\x1b[1;31m%d tests failed for %s\x1b[0m\n", test.failures, test.id);
    printf("-----\n");
}

static void assert(Test *test, bool expected, const char *error_msg)
{
    // increase total test counter
    ++test->assertions;

    // return if check is true, meaning test is valid
    if (expected)
        return;

    printf("failed: %s\n", error_msg);

    // increase failures counter
    ++test->failures;
    // set it as false
    // no matter how many checks will executed within the test
    // if one fails, the test fails.
    test->result = false;
}
