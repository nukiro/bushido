#pragma once

#include <string.h>
#include <stdbool.h>

// Check whether a returned status indicates success.
bool was_executed_successfully(int status);
bool is_array_empty(const char *arr, size_t size);