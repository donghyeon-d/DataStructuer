#include "simulation.h"

// Linked Queue

LinkedQueue* createLinkedQueue()
{
    LinkedQueue *newLinkedQueue;

    newLinkedQueue = (LinkedQueue *)malloc(sizeof(LinkedQueue));
    if (newLinkedQueue == NULL)
        return (NULL);
    newLinkedQueue->currentElementCount = 0;
    newLinkedQueue->pFrontNode = NULL;
    newLinkedQueue->pRearNode = NULL;
    return (newLinkedQueue);
}

int isLinkedQueueEmpty(LinkedQueue* pLQueue)
{
    if (pLQueue == NULL)
        return (ERROR);
    if (pLQueue->currentElementCount == 0)
        return (TRUE);
    else
        return (FALSE);
}

int enqueueLQ(LinkedQueue* pLQueue, LinkedQueueNode *element)
{
    LinkedQueueNode *newLinkedQueueNode;

    if (pLQueue == NULL)
        return (ERROR);
    newLinkedQueueNode = (LinkedQueueNode *)malloc(sizeof(LinkedQueueNode));
    if (newLinkedQueueNode == NULL)
        return (FALSE);
    newLinkedQueueNode->customer = element->customer;
    newLinkedQueueNode->pLink = NULL;
    if (isLinkedQueueEmpty(pLQueue))
    {
        pLQueue->pFrontNode = newLinkedQueueNode;
        pLQueue->pRearNode = newLinkedQueueNode;
    }
    else
    {
        pLQueue->pRearNode->pLink = newLinkedQueueNode;
        pLQueue->pRearNode = newLinkedQueueNode;
    }
    pLQueue->currentElementCount++;
    return (TRUE);
}

LinkedQueueNode *dequeueLQ(LinkedQueue* pLQueue)
{
    LinkedQueueNode *lq;

    if (pLQueue == NULL)
    {
        printf("LinkedQueue is NULL\n");
        return (NULL);
    }
    if (isLinkedQueueEmpty(pLQueue))
    {
        printf("LinkedQueue is Empty\n");
        return (NULL);
    }
    lq = pLQueue->pFrontNode;
    if (pLQueue->currentElementCount == 1)
    {
        pLQueue->pFrontNode = NULL;
        pLQueue->pRearNode = NULL;
        pLQueue->currentElementCount--;
    }
    else
    {
        pLQueue->pFrontNode = pLQueue->pFrontNode->pLink;
        pLQueue->currentElementCount--;
    }
    return (lq);
}

LinkedQueueNode *peekLQ(LinkedQueue* pLQueue)//copy
{
    LinkedQueueNode *lq;

    if (pLQueue == NULL)
    {
        printf("LinkedQueue is NULL\n");
        return (NULL);
    }
    if (isLinkedQueueEmpty(pLQueue))
    {
        printf("LinkedQueue is Empty\n");
        return (NULL);
    }
    // lq = (LinkedQueueNode *)malloc(sizeof(LinkedQueueNode));
    // if (lq == NULL)
    //     return (NULL);
    lq->customer = pLQueue->pFrontNode->customer;
    lq->pLink = pLQueue->pFrontNode->pLink;
    return (lq);
}

void deleteLinkedQueue(LinkedQueue* pLQueue)
{
    LinkedQueueNode *temp;

    if (pLQueue == NULL)
        return ;
    if (isLinkedQueueEmpty(pLQueue))
    {
        printf("LinkedQueue is Empty\n");
        return ;
    }
    while (pLQueue->currentElementCount > 0)
    {
        temp = dequeueLQ(pLQueue);
        free(temp);
    }
    free(pLQueue);
    pLQueue = NULL;
}

LinkedQueue* copyLinkedQueue(LinkedQueue* pLQueue)
{
    LinkedQueue     *newLinkedQueue;
    LinkedQueueNode *temp;

    newLinkedQueue = (LinkedQueue *)malloc(sizeof(LinkedQueue));
    if (newLinkedQueue == NULL)
        return (NULL);
    temp = pLQueue->pFrontNode;
    while (temp)
    {
        enqueueLQ(newLinkedQueue, temp);
        temp = temp->pLink;
    }
    return (newLinkedQueue);
}

void    displayLQ(LinkedQueue* pLQueue)
{
    LinkedQueueNode *temp;

    if (pLQueue == NULL)
        printf("ArrayQueue is NULL\n");
    else if (isLinkedQueueEmpty(pLQueue))
        printf("ArrayQueue is Empty\n");
    else
    {
        temp = pLQueue->pFrontNode;
        printf("front ");
        while (temp)
        {
            printf("| %d, %d ", temp->customer.arrivalTime, temp->customer.serviceTime);
            temp = temp->pLink;
        }
        printf("| end\n");
    }
}


// Array Circular Queue

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