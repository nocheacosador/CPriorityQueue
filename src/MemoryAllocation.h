#pragma once

#include <stdlib.h>

/**
 * @brief stdlib malloc wrapper
 * 
 * @param size 
 * @return void* 
 */
void* Malloc(size_t size);

/**
 * @brief stdlib free wrapper
 * 
 * @param ptr 
 */
void Free(void* ptr);

/**
 * @brief Prints succesful malloc and free call count 
 */
void PrintMemoryAllocationReport();