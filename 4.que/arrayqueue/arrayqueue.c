#include "arrayqueue.h"

ArrayQueue	*createArrayQueue(int maxElementCount)
{
	ArrayQueue	*rt_ArrayQueue;

	if (maxElementCount <= 0)
		return (NULL);
	rt_ArrayQueue = malloc(sizeof(ArrayQueue));
	if (!rt_ArrayQueue)
		return (NULL);
	// maxElementCount 만큼 공간할당.
	rt_ArrayQueue->pElement = malloc(sizeof(ArrayQueueNode) * maxElementCount);
	if (!(rt_ArrayQueue->pElement))
		return (NULL);
	// max 초기값 세팅.
	rt_ArrayQueue->maxElementCount = maxElementCount;
	// 현재는 아무것도 add가 안됐으므로 currCnt, front, rear는 0으로 초기화
	rt_ArrayQueue->currentElementCount = 0;
	rt_ArrayQueue->front = 0;
	rt_ArrayQueue->rear = 0;
	return (rt_ArrayQueue);
}

int	enqueueAQ(ArrayQueue *pQueue, ArrayQueueNode element)
{
	int	curr;

	// pQueue가 NULL이거나 가득 차있으면 return 0.
	if (!pQueue || isArrayQueueFull(pQueue))
		return (FALSE);
	curr = pQueue->currentElementCount;
	pQueue->pElement[curr] = element;
	pQueue->currentElementCount += 1;
	pQueue->rear = (pQueue->currentElementCount) - 1;
	return (curr + 1);
}

int	dequeueAQ(ArrayQueue *pQueue)
{ // 앞에 애를 빼면 하나씩 앞으로 밀어줘야겠구나
	int	rt_value;
	int	idx;
	int	rear;

	if (!pQueue || isArrayQueueEmpty(pQueue))
		return (FALSE);
	rt_value = peekAQ(pQueue);
	rear = pQueue->rear;
	// 현재 rear의 data를 0으로 초기화.
	// front를 0번째로 해주기 위해서 왼쪽으로 하나씩 이동.
	idx = 0;
	while (idx < rear)
	{
		pQueue->pElement[idx].data = pQueue->pElement[idx + 1].data;
		idx++;
	}
	// rear.data = 0;
	pQueue->pElement[idx].data = 0;
	pQueue->currentElementCount -= 1;
	pQueue->rear -= 1;
	return (rt_value);
}

int	peekAQ(ArrayQueue *pQueue)
{
	if (!pQueue || isArrayQueueEmpty(pQueue))
		return (FALSE);
	return (pQueue->pElement[0].data);
}

void	deleteArrayQueue(ArrayQueue *pQueue)
{
	if (!pQueue)
		return ;
	free (pQueue->pElement);
	free (pQueue);
}

int	isArrayQueueFull(ArrayQueue *pQueue)
{
	if (pQueue->currentElementCount == pQueue->maxElementCount
		|| pQueue->rear == pQueue->maxElementCount - 1)
		return (TRUE);
	else
		return (FALSE);
}

int	isArrayQueueEmpty(ArrayQueue *pQueue)
{
	if (pQueue->currentElementCount == 0)
		return (TRUE);
	else
		return (FALSE);
}

void	displayArrayQueue(ArrayQueue *pQueue)
{
	int	idx;
	int	crnt;

	if (!pQueue)
		return ;
	if (isArrayQueueEmpty(pQueue))
		printf("isEmpty\n");
	crnt = pQueue->currentElementCount;
	idx = 0;
	while (idx < crnt)
	{
		printf("%3d | ", pQueue->pElement[idx].data);
		idx++;
	}
	printf("\b\n");
}

int	getArrayQueueLength(ArrayQueue *pQueue)
{
	if (!pQueue)
		return (0);
	return (pQueue->currentElementCount);
}