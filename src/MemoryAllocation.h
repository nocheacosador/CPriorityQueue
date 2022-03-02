#pragma once

#include <stdlib.h>

void* Malloc(size_t size);
void Free(void* ptr);
void PrintMemoryAllocationReport();