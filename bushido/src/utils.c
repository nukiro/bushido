#include <utils.h>

bool was_executed_successfully(int status)
{
    return status == 1;
}

bool is_array_empty(const char *arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] != '\0')
        {
            return false; // Not empty
        }
    }
    return true; // All zeros
}