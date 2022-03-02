#include "MemoryAllocation.h"

#include <stdio.h>

static size_t s_MallocCount = 0;
static size_t s_FreeCount = 0;

void* Malloc(size_t size)
{
    void* ptr = malloc(size);
    if (ptr) s_MallocCount++;
    return ptr;
}

void Free(void* ptr)
{
    s_FreeCount++;
    free(ptr);
}

void PrintMemoryAllocationReport()
{
    printf( "[Memmory Allocation Report]\n"
            "  malloc count: %lu\n"
            "  free count: %lu\n",
            s_MallocCount, s_FreeCount);
}