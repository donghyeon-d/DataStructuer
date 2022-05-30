#ifndef _ARRAY_QUEUE_
#define _ARRAY_QUEUE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ArrayQueueNodeType
{
	int data;
} ArrayQueueNode;

typedef struct ArrayQueueType
{
	int 			maxElementCount;		// 최대 원소 개수
	int 			currentElementCount;	// 현재 원소 개수
	int 			front;					// front 위치 디큐
	int 			rear;					// rear 위치 인큐
	ArrayQueueNode	*pElement;				// 노드 저장을 위한 1차원 배열 포인터
} ArrayQueue;

ArrayQueue	*createArrayQueue(int maxElementCount);
int			enqueueAQ(ArrayQueue *pQueue, ArrayQueueNode element);
int			dequeueAQ(ArrayQueue *pQueue);
int			peekAQ(ArrayQueue *pQueue);
void		deleteArrayQueue(ArrayQueue *pQueue);
int			isArrayQueueFull(ArrayQueue *pQueue);
int			isArrayQueueEmpty(ArrayQueue *pQueue);
void		displayArrayQueue(ArrayQueue *pQueue);
int			getArrayQueueLength(ArrayQueue *pQueue);

#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_

#define TRUE		1
#define FALSE		0

#endif