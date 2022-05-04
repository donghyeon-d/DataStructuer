#include <stdlib.h>
#include <stdio.h>
#include "arrayqueue_dongchoi.h"

ArrayQueue* createArrayQueue(int maxElementCount)
{
    ArrayQueue      *newArrayQueue;
    ArrayQueueNode  *pElement;

    newArrayQueue = (ArrayQueue *)malloc(sizeof(ArrayQueue));
    if (newArrayQueue == NULL)
        return (NULL);
    pElement = (ArrayQueueNode *)malloc(sizeof(ArrayQueueNode) * maxElementCount);
    if (pElement == NULL)
    {
        free(newArrayQueue);
        return (NULL);
    }
    newArrayQueue->pElement = pElement;
    newArrayQueue->maxElementCount = maxElementCount;
    newArrayQueue->currentElementCount = 0;
    newArrayQueue->front = 0;
    newArrayQueue->rear = 0;
    return (newArrayQueue);
}

int isArrayQueueFull(ArrayQueue* pQueue)
{
    if (pQueue == NULL)
        return (ERROR);
    if (pQueue->maxElementCount == pQueue->rear + 1)
        return (TRUE);
    return (FALSE);
}

int isArrayQueueEmpty(ArrayQueue* pQueue)
{
    if (pQueue == NULL)
        return (ERROR);
    if (pQueue->currentElementCount == 0 && !isArrayQueueFull(pQueue))
        return (TRUE);
    return (FALSE);
}

int canEnqueueCount(ArrayQueue* pQueue)
{
    return (pQueue->maxElementCount - (pQueue->rear + 1));
}

int enqueueAQ(ArrayQueue* pQueue, ArrayQueueNode element)
{
    if (isArrayQueueFull(pQueue) || pQueue == NULL)
        return (ERROR);
    if (isArrayQueueEmpty(pQueue))
        pQueue->rear = pQueue->front;
    else
        pQueue->rear++;
    (pQueue->pElement)[pQueue->rear] = element;
    pQueue->currentElementCount++;
    return (TRUE);
}

ArrayQueueNode *dequeueAQ(ArrayQueue* pQueue)
{
    ArrayQueueNode *dequeue;

    if (isArrayQueueEmpty(pQueue) > 0)
    {
        printf("ArrayQueue is Empty\n");
        return(NULL);
    }
    if (pQueue == NULL)
    {
        printf("ArrayQueue is NULL\n");
        return (NULL);
    }
    dequeue = &(pQueue->pElement)[pQueue->front];
    pQueue->currentElementCount--;
    pQueue->front++;
    return (dequeue);
}

ArrayQueueNode *peekAQ(ArrayQueue* pQueue)
{
    if (isArrayQueueEmpty(pQueue))
    {
        printf("ArrayQueue is Empty\n");
        return(NULL);
    }
    if (pQueue == NULL)
    {
        printf("ArrayQueue is NULL\n");
        return (NULL);
    }
    return (&(pQueue->pElement)[pQueue->front]);
}

void deleteArrayQueue(ArrayQueue* pQueue)
{
    if (pQueue == NULL)
        return ;
    free(pQueue->pElement);
    free(pQueue);
}

ArrayQueue* copyArrayQueue(ArrayQueue* pQueue)
{
    ArrayQueue  *newArrayQueue;
    int         n;

    if (pQueue == NULL)
        return (NULL);
    newArrayQueue = createArrayQueue(pQueue->maxElementCount);
    if (newArrayQueue == NULL)
        return (NULL);
    newArrayQueue->maxElementCount = pQueue->maxElementCount;
    newArrayQueue->currentElementCount = pQueue->currentElementCount;
    newArrayQueue->front = pQueue->front;
    newArrayQueue->rear = pQueue->rear;
    n = 0;
    while(n < newArrayQueue->currentElementCount)
    {
        newArrayQueue->pElement[newArrayQueue->front + n] = pQueue->pElement[newArrayQueue->front + n];
        n++;
    }
    return (newArrayQueue);
}

void    displayAq(ArrayQueue* pQueue)
{
    int n;

    n = -1;
    if (pQueue == NULL)
        printf("ArrayQueue is NULL\n");
    else if (isArrayQueueEmpty(pQueue))
        printf("ArrayQueue is Empty\n");
    else
    {
        printf("front ");
        while (++n < pQueue->currentElementCount)
            printf("| %c ", (pQueue->pElement[pQueue->front + n]).data);
        printf("| end\n");
    }
}

int main()
{
    ArrayQueue *aq;
    ArrayQueue *aq2;
    ArrayQueueNode *temp;

    // createArrayQueue
    aq = createArrayQueue(5);
    printf("< createArrayQueue >\n");
    displayAq(aq);
    printf("Maxcount : %d\n", aq->maxElementCount);
    
    printf("\n< isArrayQueueEmpty >\n");
    printf("isArrayQueueEmpty : %d\n", isArrayQueueEmpty(aq));

    printf("\n< enqueueAQ 3times >\n");
    enqueueAQ(aq, (ArrayQueueNode){'a'});
    displayAq(aq);
    enqueueAQ(aq, (ArrayQueueNode){'b'});
    displayAq(aq);
    enqueueAQ(aq, (ArrayQueueNode){'c'});
    displayAq(aq);

    printf("\n< canEnqueueCount >\n");
    printf("canEnqueueCount : %d\n", canEnqueueCount(aq));

    printf("\n< enqueueAQ 2times >\n");
    enqueueAQ(aq, (ArrayQueueNode){'d'});
    displayAq(aq);
    enqueueAQ(aq, (ArrayQueueNode){'e'});
    displayAq(aq);

    printf("\n< isArrayQueueFull >\n");
    printf("isArrayQueueFull : %d\n", isArrayQueueFull(aq));

    printf("\n< copyArrayQueue >\n");
    aq2 = copyArrayQueue(aq);
    displayAq(aq2);

    printf("\n< dequeueAQ 3times >\n");
    temp = dequeueAQ(aq); printf("dequeueAQ.data : %c | ", temp->data); displayAq(aq);
    temp = dequeueAQ(aq); printf("dequeueAQ.data : %c | ", temp->data); displayAq(aq);
    temp = dequeueAQ(aq); printf("dequeueAQ.data : %c | ", temp->data); displayAq(aq);

    printf("\n< peekAQ >\n");
    temp = peekAQ(aq);
    printf("peekAQ : %c\n", temp->data);

    printf("\n< deleteArrayQueue >\n");
    deleteArrayQueue(aq);
    aq = NULL;
    displayAq(aq);
    system("leaks a.out");
}