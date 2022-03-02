#include "PriorityQueue.h"

#include <assert.h>
#include "MemoryAllocation.h"

void PriorityQueue_Insert(PriorityQueue* queue, int priority, void* data)
{
    assert(queue != NULL);

    // construct new node
    PriorityQueueNode* new = (PriorityQueueNode*)Malloc(sizeof(PriorityQueueNode));
    if (new == NULL) 
    {
        perror("Error while creating new priority queue node");
        return;
    }

    new->priority = priority;
    new->data = data;

    // find where to insert node
    PriorityQueueNode* node = queue->first;
    PriorityQueueNode* prev = NULL;
    for ( ; node != NULL; node = node->next)
    {
        if (node->priority < new->priority) break;
        prev = node;
    }

    if (prev == NULL) // insert first
    {
        new->next = queue->first;
        queue->first = new;
    }
    else 
    {
        new->next = prev->next;
        prev->next = new;
    }

    queue->size++;
}

void* PriorityQueue_Pop(PriorityQueue* queue)
{
    assert(queue != NULL);

    if (queue->first == NULL) 
        return NULL;
    
    void* data = queue->first->data;
    PriorityQueueNode* toFree = queue->first;
    queue->first = queue->first->next;
    Free(toFree);
    queue->size--;
    
    return data;
}

void* PriorityQueue_Peek(PriorityQueue* queue)
{
    assert(queue != NULL);

    if (queue->first == NULL) 
        return NULL;
    
    return queue->first->data;
}

int PriorityQueue_IsEmpty(PriorityQueue* queue)
{
    assert(queue != NULL);

    return queue->first == NULL;
}

void PriorityQueue_Join(PriorityQueue* queue1, PriorityQueue* queue2)
{
    assert(queue1 != NULL);
    assert(queue2 != NULL);
    assert(queue1 != queue2);

    PriorityQueueNode* queue1_node = queue1->first;
    PriorityQueueNode* queue1_prev = NULL;
    
    PriorityQueueNode* queue2_node = queue2->first;
    PriorityQueueNode* queue2_nextNode = NULL;
    
    for ( ; queue2_node != NULL; queue2_node = queue2_nextNode)
    {
        queue2_nextNode = queue2_node->next;

        for ( ; queue1_node != NULL; queue1_node = queue1_node->next)
        {
            if (queue1_node->priority < queue2_node->priority) break;
            queue1_prev = queue1_node;
        }

        if (queue1_prev == NULL)
        {
            queue2_node->next = queue1->first;
            queue1->first = queue2_node;
        }
        else
        {
            queue2_node->next = queue1_prev->next;
            queue1_prev->next = queue2_node;
        }

        queue1->size++;
        queue2->size--;
    }

    queue2->first = NULL;
}

static char* defaultToString(void* data) 
{
    size_t needed = snprintf(NULL, 0, "adress: 0x%p", data) + 1;
    char* buffer = Malloc(needed);
    sprintf(buffer, "adress: 0x%p", data);
    return buffer;
}

void PriorityQueue_Print(PriorityQueue* queue, ToStringFunc* toStringFunc, FILE* stream)
{
    assert(queue != NULL);

    if (toStringFunc == NULL) toStringFunc = defaultToString;

    for (PriorityQueueNode* node = queue->first; node != NULL; node = node->next)
    {
        char* data = toStringFunc(node->data);
        fprintf(stream, "priority: %d data: %s\n", node->priority, data);
        Free(data);
    }

    fprintf(stream, "Size: %d\n", queue->size);
}