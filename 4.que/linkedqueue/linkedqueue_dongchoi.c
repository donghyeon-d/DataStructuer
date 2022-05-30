#include <stdlib.h>
#include <stdio.h>
#include "linkedqueue_dongchoi.h"

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
    LinkedQueueNode *newNode;

    if (pLQueue == NULL || element == NULL)
        return (ERROR);
    newNode = malloc(sizeof(LinkedQueueNode));
    if (newNode == NULL)
        return (FALSE);
    *newNode = *element;
    newNode->pLink = NULL;
    if (isLinkedQueueEmpty(pLQueue))
    {
        pLQueue->pFrontNode = newNode;
        pLQueue->pRearNode = newNode;
    }
    else
    {
        pLQueue->pRearNode->pLink = newNode;
        pLQueue->pRearNode = newNode;
    }
    pLQueue->currentElementCount++;
    return (TRUE);
}

LinkedQueueNode *dequeueLQ(LinkedQueue* pLQueue)
{
    LinkedQueueNode *dequeNode;

    if (pLQueue == NULL || isLinkedQueueEmpty(pLQueue))
        return (NULL);
    dequeNode = pLQueue->pFrontNode;
    pLQueue->pFrontNode = pLQueue->pFrontNode->pLink;
    pLQueue->currentElementCount--;
    return (dequeNode);
}

LinkedQueueNode *peekLQ(LinkedQueue* pLQueue)//copy
{
    if (pLQueue == NULL || isLinkedQueueEmpty(pLQueue))
        return (NULL);
    return (pLQueue->pFrontNode);
}

void deleteLinkedQueue(LinkedQueue* pLQueue)
{
    LinkedQueueNode *temp;

    if (pLQueue == NULL)
        return ;
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
            printf("| %c ", temp->data);
            temp = temp->pLink;
        }
        printf("| end\n");
    }
}

int main()
{
    LinkedQueue *lq;
    LinkedQueue *lq2;
    LinkedQueueNode *temp;

    // createArrayQueue
    lq = createLinkedQueue();
    printf("< createLinkedQueue >\n");
    displayLQ(lq);
    
    printf("\n< isLinkedQueueEmpty >\n");
    printf("isLinkedQueueEmpty : %d\n", isLinkedQueueEmpty(lq));

    printf("\n< enqueueLQ 3times >\n");
    enqueueLQ(lq, &((LinkedQueueNode){'a', NULL}));
    displayLQ(lq);
    enqueueLQ(lq, &((LinkedQueueNode){'b', NULL}));
    displayLQ(lq);
    enqueueLQ(lq, &((LinkedQueueNode){'c', NULL}));
    displayLQ(lq);

    // printf("\n< canEnqueueCount >\n");
    // printf("canEnqueueCount : %d\n", canEnqueueCount(lq));

    printf("\n< enqueueLQ 2times >\n");
    enqueueLQ(lq, &((LinkedQueueNode){'d', NULL}));
    displayLQ(lq);
    enqueueLQ(lq, &((LinkedQueueNode){'e', NULL}));
    displayLQ(lq);

    printf("\n< copyLinkedQueue >\n");
    lq2 = copyLinkedQueue(lq);
    displayLQ(lq2);

    printf("\n< dequeueLQ 3times >\n");
    temp = dequeueLQ(lq); printf("dequeueLQ->data : %c | ", temp->data); displayLQ(lq); free(temp);
    temp = dequeueLQ(lq); printf("dequeueLQ->data : %c | ", temp->data); displayLQ(lq); free(temp);
    temp = dequeueLQ(lq); printf("dequeueLQ->data : %c | ", temp->data); displayLQ(lq); free(temp);

    printf("\n< peekLQ >\n");
    temp = peekLQ(lq);
    printf("peekLQ : %c\n", temp->data);

    printf("\n< deleteLinkedQueue >\n");
    deleteLinkedQueue(lq);
    lq = NULL;
    displayLQ(lq);

    printf("\n< leaks check >\n");
    system("leaks a.out");
}