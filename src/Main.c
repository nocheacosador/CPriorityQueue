#include <stdio.h>
#include <string.h>
#include "PriorityQueue.h"
#include "MemoryAllocation.h"

int* HeapInt(int val)
{
    int* ptr = (int*)Malloc(sizeof(int));
    *ptr = val;
    return ptr;
}

char* IntToString(void* data)
{
    size_t needed = snprintf(NULL, 0, "%d", *(int*)data) + 1;
    char* buffer = Malloc(needed);
    sprintf(buffer, "%d", *(int*)data);
    return buffer;
}

int main()
{
    PriorityQueue queue[4];
    int slotID = 0;
    
    for (int i = 0; i < 4; i++)
        queue[i] = PriorityQueue_Create();

    char buf[1024];
    int run = 1;
    while (run) 
    {    
        printf("> ");
        scanf("%s", buf);

        if (!strcmp("insert", buf))
        {
            int priority, data;
            scanf("%d %d", &priority, &data);
    
            PriorityQueue_Insert(&queue[slotID], priority, HeapInt(data));
        }
        else if (!strcmp("pop", buf))
        {
            int* data = (int*)PriorityQueue_Pop(&queue[slotID]);
            
            if (data == NULL)
            {
                puts("NULL");
            }
            else
            {
                printf("%d\n", *data);
                Free(data);
            }
        }
        else if (!strcmp("isEmpty", buf))
        {
            puts( PriorityQueue_IsEmpty(&queue[slotID]) ? "true" : "false" );
        }
        else if (!strcmp("peek", buf))
        {
            int* data = (int*)PriorityQueue_Peek(&queue[slotID]);
            
            if (data == NULL)
            {
                puts("NULL");
            }
            else
            {
                printf("%d\n", *data);
            }
        }
        else if (!strcmp("join", buf))
        {
            int joinID;
            scanf("%d", &joinID);

            if (joinID < 0 || joinID > 3)
            {
                puts("ID out of range. ID can be from 0 to 3.");
                continue;
            }
            else if (joinID == slotID)
            {
                puts("Can't join queue with it self.");
                continue;
            }

            PriorityQueue_Join(&queue[slotID], &queue[joinID]);
        }
        else if (!strcmp("bind", buf))
        {
            int id;
            scanf("%d", &id);

            if (id >= 0 && id < 4)
            {
                slotID = id;
            }
            else
            {
                puts("ID out of range. ID can be from 0 to 3.");
            }
        }
        else if (!strcmp("print", buf))
        {
            printf("Queue[%d]:\n", slotID); 
            PriorityQueue_Print(&queue[slotID], IntToString, stdout);
        }
        else if (!strcmp("quit", buf))
        {
            puts("Bye.");
            run = 0;
        }
        else
        {
            printf("Unknown command: '%s'\n", buf);
            continue;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        while (!PriorityQueue_IsEmpty(&queue[i]))
        {
            Free(PriorityQueue_Pop(&queue[i]));
        }
    }

    PrintMemoryAllocationReport();
}