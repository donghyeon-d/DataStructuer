#include <stdlib.h>
#include <stdio.h>
#include "arrayqueue.h"

ArrayQueue* createArrayQueue(int maxElementCount)
{
	ArrayQueue *pQueue;

	pQueue = (ArrayQueue *)malloc(sizeof(ArrayQueue));
	pQueue->maxElementCount = maxElementCount;
	pQueue->currentElementCount = 0;
	pQueue->front = 0;
	pQueue->rear = 0;
	pQueue->pElement = (ArrayQueueNode *)malloc(sizeof(ArrayQueueNode) * maxElementCount);
	return (pQueue);
}

int enqueueAQ(ArrayQueue* pQueue, ArrayQueueNode element)
{
	if (isArrayQueueFull(pQueue))
		return (FALSE);
	if (isArrayQueueEmpty(pQueue))
		pQueue->pElement[0] = element;
	else if (pQueue->rear == pQueue->maxElementCount -1)
	{
		pQueue->pElement[pQueue->currentElementCount - (pQueue->rear - pQueue->front + 1)] = element;
		pQueue->rear++;
	}
	else
	{
		pQueue->pElement[pQueue->rear + 1] = element;
		pQueue->rear++;
	}
	pQueue->currentElementCount++;
	if (pQueue->rear == pQueue->maxElementCount)
		pQueue->rear = 0;
	return (TRUE);
}

ArrayQueueNode *dequeueAQ(ArrayQueue* pQueue)
{
	if (isArrayQueueEmpty(pQueue))
		return (FALSE);
	ArrayQueueNode *ret;
	ret = (ArrayQueueNode *)malloc(sizeof(ArrayQueueNode));
	ret->data = peekAQ(pQueue)->data;
	pQueue->currentElementCount--;
	pQueue->front++;
	if (pQueue->front == pQueue->maxElementCount)
		pQueue->front = 0;
	return (ret);
}

ArrayQueueNode *peekAQ(ArrayQueue* pQueue)
{
	if (isArrayQueueEmpty(pQueue))
		return (FALSE);
	return (&pQueue->pElement[pQueue->front]);
}

void deleteArrayQueue(ArrayQueue* pQueue)
{
	if (pQueue == NULL)
		return;
	free(pQueue->pElement);
	free(pQueue);
}

int isArrayQueueFull(ArrayQueue* pQueue)
{
	if (pQueue->maxElementCount == pQueue->currentElementCount && pQueue->currentElementCount != 0)
		return (TRUE);
	return (FALSE);
}

int isArrayQueueEmpty(ArrayQueue* pQueue)
{
	if (pQueue->currentElementCount == 0)
		return (TRUE);
	return (FALSE);
}

void displayArrayQueue(ArrayQueue *pQueue)
{
	if (pQueue == NULL)
		printf("Queue is NULL\n");
	if (isArrayQueueEmpty(pQueue))
		printf("Queue is empty\n");
	printf("max count:%d | current count:%d\n", pQueue->maxElementCount, pQueue->currentElementCount);
	printf("front index:%d rear index:%d\n", pQueue->front, pQueue->rear);
	printf("|");
	if (pQueue->front < pQueue->rear)
	{
		for (int i = pQueue->front; i <= pQueue->rear; i++)
		{
			printf("%c|", pQueue->pElement[i].data);
		}
	}
	else
	{
		for (int i = pQueue->front; i < pQueue->maxElementCount; i++)
		{
			printf("%c|", pQueue->pElement[i].data);
		}
		printf(" ");
		for (int i = 0; i <= pQueue->rear; i++)
		{
			printf("%c|", pQueue->pElement[i].data);
		}
	}
	printf("\n");
}

/*int main()
{
	ArrayQueue *pQueue;
	ArrayQueueNode temp;
	ArrayQueueNode *tmp;

	pQueue = createArrayQueue(10);
	for (int i = 0; i < pQueue->maxElementCount; i++)
	{
		temp.data = i + 65;
		enqueueAQ(pQueue, temp);
	}
	displayArrayQueue(pQueue);
	tmp = peekAQ(pQueue);
	printf("\npeek : %c\n", tmp->data);
	tmp = NULL;
	tmp = dequeueAQ(pQueue);
	printf("delete : %c\n\n", tmp->data);
	displayArrayQueue(pQueue);
	printf("\n");
	temp.data = 'K';
	enqueueAQ(pQueue, temp);
	displayArrayQueue(pQueue);
}*/
		
