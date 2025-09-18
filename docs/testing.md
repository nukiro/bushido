# Testing

In our source code we define our test and register them.

```c
#ifdef TEST

#include "test.h"
#include "string.h"

static void test_manager_init(Test *t)
{
    const char *current = "A0001";

    Manager m = manager_init(current);

    bool check = strcmp(m.navigation.current, "A0001") == 0;
    assert(t, check, "manager_init should initialize current navigation");
}

void manager_tests(void)
{
    Test t = {"Manager", true, 0, 0};

    test_manager_init(&t);

    result(t);
}
#endif
```

Run registered tests in the test runner.
