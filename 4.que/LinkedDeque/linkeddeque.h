#ifndef _LINKED_DEQUE_
#define _LINKED_DEQUE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DequeNodeType
{
	char					data;
	struct DequeNodeType	*pRLink;
	struct DequeNodeType	*pLLink;
} DequeNode;

typedef struct LinkedDequeType
{
	int			currentElementCount;	// 현재 원소의 개수
	DequeNode	*pFrontNode;			// Front 노드의 포인터
	DequeNode	*pRearNode;				// Rear 노드의 포인터
} LinkedDeque;

LinkedDeque	*createLinkedDeque(); // 
int 		insertFront(LinkedDeque *pDeque, DequeNode element);
int 		insertRear(LinkedDeque *pDeque, DequeNode element);
DequeNode	*deleteFront(LinkedDeque *pDeque);
DequeNode	*deleteRear(LinkedDeque *pDeque);
DequeNode	*peekFront(LinkedDeque *pDeque);
DequeNode	*peekRear(LinkedDeque *pDeque);
void		deleteLinkedDeque(LinkedDeque *pDeque);
int			isLinkedDequeEmpty(LinkedDeque *pDeque);

#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_

#define TRUE		1
#define FALSE		0

#endif