# Testing

```c
// mathx.h
int add(int a, int b);
```

In our `C` source code we define our test and register them.

```c
// mathx.c
int add(int a, int b) { return a + b; }

#ifdef TEST
#include "../tests/test.h"

static void test_add(Test *t)
{
    assert(t, add(2, 3) == 4, "add(2,3) should be 5");
    if (t->result)
        printf("test was good\n");
    else
        printf("test was not good\n");
}

void mathx_register_tests(void)
{
    Test t = {true, 0, 0};

    test_add(&t);
}
#endif
```

Run registered tests in the test runner.
