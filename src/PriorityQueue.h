#pragma once

#include <stddef.h>
#include <stdio.h>

/**
 * @brief Priority queue node
 */
typedef struct PriorityQueueNode {
    int priority;
    void* data;
    struct PriorityQueueNode* next;
} PriorityQueueNode;

/**
 * @brief Priority queue structure
 */
typedef struct PriorityQueue 
{
    struct PriorityQueueNode* first;
    int size;
} PriorityQueue;


/**
 * @brief Creates empty priority queue
 * 
 * @return empty priority queue
 */
static inline PriorityQueue PriorityQueue_Create()
{
    return (PriorityQueue){ NULL, 0 };
}

/**
 * @brief Inserts data into the queue with priority
 * 
 * @param queue pointer to a queue where to insert data
 * @param priority priority of the data 
 * @param data pointer to data to be inserted
 */
void PriorityQueue_Insert(PriorityQueue* queue, int priority, void* data);

/**
 * @brief Deletes data with the highest priority from the list and then returns it
 * 
 * @param queue pointer to a queue
 * @return pointer to data with the highest priority,
 *         NULL if queue is empty
 */
void* PriorityQueue_Pop(PriorityQueue* queue);

/**
 * @brief Same as `PriorityQueue_Pop` just doesn't delete the data from the queue
 * 
 * @param queue pointer to a queue
 * @return data with the highest priority
 *         NULL if queue is empty
 */
void* PriorityQueue_Peek(const PriorityQueue* queue);

/**
 * @brief Checks if queue is empty
 * 
 * @param queue pointer to a queue
 * @return 1 if empty, 0 if not empty
 */
int PriorityQueue_IsEmpty(const PriorityQueue* queue);

/**
 * @brief Deletes priority queue and frees all of it's members
 * 
 * @param queue pointer to priority queue
 */
void PriorityQueue_Delete(PriorityQueue* queue)

/**
 * @brief Joins two queues together
 * 
 * @param queue1 pointer to a queue to witch to join
 * @param queue2 pointer to a queue that is to be joined
 */
void PriorityQueue_Join(PriorityQueue* queue1, PriorityQueue* queue2);

/**
 * @brief Function type for data conversion to string.
 *        Takes in pointer to data that needs to be printed.
 * 
 * @return heap allocated string
 */
typedef char* ToStringFunc(void*);

/**
 * @brief Prints priority queue content to stream
 * 
 * @param queue pointer to a queue to be printed
 * @param toStringFunc pointer to a function of type `ToStringFunc`,
 *                     if NULL - default function is used
 * @param stream where to print
 */
void PriorityQueue_Print(const PriorityQueue* queue, ToStringFunc* toStringFunc, FILE* stream);