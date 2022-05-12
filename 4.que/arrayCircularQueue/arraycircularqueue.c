#include <stdlib.h>
#include <stdio.h>
#include "arraycircularqueue.h"



ArrayCircularQueue* createArrayCircularQueue(int maxElementCount)
{
    ArrayCircularQueue      *newArrayCircularQueue;
    ArrayCircularQueueNode  *pElement;

    newArrayCircularQueue = (ArrayCircularQueue *)malloc(sizeof(ArrayCircularQueue));
    if (newArrayCircularQueue == NULL)
        return (NULL);
    pElement = (ArrayCircularQueueNode *)malloc(sizeof(ArrayCircularQueueNode) * maxElementCount);
    if (pElement == NULL)
    {
        free(newArrayCircularQueue);
        return (NULL);
    }
    newArrayCircularQueue->pElement = pElement;
    newArrayCircularQueue->maxElementCount = maxElementCount;
    newArrayCircularQueue->currentElementCount = 0;
    newArrayCircularQueue->front = 0;
    newArrayCircularQueue->rear = 0;
    return (newArrayCircularQueue);
}

int isArrayCircularQueueFull(ArrayCircularQueue* pACQueue)
{
    if (pACQueue == NULL)
        return (ERROR);
    if (pACQueue->maxElementCount == pACQueue->currentElementCount)
        return (TRUE);
    return (FALSE);
}

int isArrayCircularQueueEmpty(ArrayCircularQueue* pACQueue)
{
    if (pACQueue == NULL)
        return (ERROR);
    if (pACQueue->currentElementCount == 0)
        return (TRUE);
    return (FALSE);
}

int enqueueACQ(ArrayCircularQueue* pACQueue, ArrayCircularQueueNode element)
{
    if (isArrayCircularQueueFull(pACQueue))
    {
        printf("ArrayCircularQueue is Full");
        return (ERROR);
    }
    if (pACQueue == NULL)
    {
        printf("ArrayCircularQueue is NULL");
        return (ERROR);
    }
    // if (isArrayQueueEmpty(pACQueue))
    // {
    //     pACQueue->rear = 0;
    //     pACQueue->front = 0;
    // }
    if (isArrayCircularQueueEmpty(pACQueue) == 0)
        pACQueue->rear = (pACQueue->rear + 1) % pACQueue->maxElementCount;
    (pACQueue->pElement)[pACQueue->rear] = element;
    pACQueue->currentElementCount++;
    return (TRUE);
}

ArrayCircularQueueNode *dequeueACQ(ArrayCircularQueue* pACQueue)
{
    ArrayCircularQueueNode *dequeue;

    if (isArrayCircularQueueEmpty(pACQueue) > 0)
    {
        printf("ArrayCircularQueue is Empty\n");
        return(NULL);
    }
    if (pACQueue == NULL)
    {
        printf("ArrayCircularQueue is NULL\n");
        return (NULL);
    }
    dequeue = &(pACQueue->pElement)[pACQueue->front];
    pACQueue->currentElementCount--;
    pACQueue->front++;
    pACQueue->front %= pACQueue->maxElementCount;
    return (dequeue);
}

ArrayCircularQueueNode *peekACQ(ArrayCircularQueue* pACQueue)
{
    ArrayCircularQueueNode *peek;

    if (isArrayCircularQueueEmpty(pACQueue) > 0)
    {
        printf("ArrayCircularQueue is Empty\n");
        return(NULL);
    }
    if (pACQueue == NULL)
    {
        printf("ArrayCircularQueue is NULL\n");
        return (NULL);
    }
    peek = malloc(sizeof(ArrayCircularQueueNode));
    if (peek == NULL)
    {
        printf("malloc error\n");
        return (NULL);
    }
    peek->data = (pACQueue->pElement)[pACQueue->front].data;
    return (peek);
}

void deleteArrayCircularQueue(ArrayCircularQueue* pACQueue)
{
    if (pACQueue == NULL)
        return ;
    free(pACQueue->pElement);
    free(pACQueue);
}

int canCircularEnqueueCount(ArrayCircularQueue* pACQueue)
{
    return (pACQueue->maxElementCount - pACQueue->currentElementCount);
}

void    displayACq(ArrayCircularQueue* pACQueue)
{
    int n;

    n = -1;
    if (pACQueue == NULL)
        printf("ArraycircularQueue is NULL\n");
    else if (isArrayCircularQueueEmpty(pACQueue))
        printf("ArraycircularQueue is Empty\n");
    else
    {
        printf("front ");
        while (++n < pACQueue->currentElementCount)
            printf("| %c ", (pACQueue->pElement[(pACQueue->front + n) % pACQueue->maxElementCount]).data);
        printf("| end\n");
    }
}

int main()
{
    ArrayCircularQueue *acq;
    ArrayCircularQueue *acq2;
    ArrayCircularQueueNode *temp;

    // createArrayCircularQueue
    acq = createArrayCircularQueue(5);
    printf("< createArrayCircularQueue >\n");
    displayACq(acq);
    printf("Maxcount : %d\n", acq->maxElementCount);
    
    printf("\n< isArrayCircularQueueEmpty >\n");
    printf("isArrayCircularQueueEmpty : %d\n", isArrayCircularQueueEmpty(acq));

    printf("\n< enqueueACQ 3times >\n");
    enqueueACQ(acq, (ArrayCircularQueueNode){'a'});
    displayACq(acq);
    enqueueACQ(acq, (ArrayCircularQueueNode){'b'});
    displayACq(acq);
    enqueueACQ(acq, (ArrayCircularQueueNode){'c'});
    displayACq(acq);

    printf("\n< canCircularEnqueueCount >\n");
    printf("canCircularEnqueueCount : %d\n", canCircularEnqueueCount(acq));

    printf("\n< enqueueACQ 2times >\n");
    enqueueACQ(acq, (ArrayCircularQueueNode){'d'});
    displayACq(acq);
    enqueueACQ(acq, (ArrayCircularQueueNode){'e'});
    displayACq(acq);

    printf("\n< isArrayCircularQueueFull >\n");
    printf("isArrayCircularQueueFull : %d\n", isArrayCircularQueueFull(acq));

    // printf("\n< copyArrayCircularQueue >\n");
    // acq2 = copyArrayCircularQueue(acq);
    // displayACq(acq2);

    printf("\n< dequeueACQ 3times >\n");
    temp = dequeueACQ(acq); printf("dequeueACQ.data : %c | ", temp->data); displayACq(acq);
    temp = dequeueACQ(acq); printf("dequeueACQ.data : %c | ", temp->data); displayACq(acq);
    temp = dequeueACQ(acq); printf("dequeueACQ.data : %c | ", temp->data); displayACq(acq);

    printf("\n< canCircularEnqueueCount >\n");
    printf("canCircularEnqueueCount : %d\n", canCircularEnqueueCount(acq));

    printf("\n< enqueueACQ 3times >\n");
    enqueueACQ(acq, (ArrayCircularQueueNode){'f'});
    displayACq(acq);
    enqueueACQ(acq, (ArrayCircularQueueNode){'g'});
    displayACq(acq);
    enqueueACQ(acq, (ArrayCircularQueueNode){'h'});
    displayACq(acq);

    printf("\n< peekACQ >\n");
    temp = peekACQ(acq);
    printf("peekACQ : %c\n", temp->data);

    printf("\n< deleteArrayCircularQueue >\n");
    deleteArrayCircularQueue(acq);
    acq = NULL;
    displayACq(acq);
    system("leaks a.out");
}