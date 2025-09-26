#include <utils.h>
#include <common.h>

bool was_executed_successfully(int status)
{
    return status == STATUS_OK;
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