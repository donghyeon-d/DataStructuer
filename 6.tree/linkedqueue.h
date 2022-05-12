#ifndef _LINKED_DEQUE_
#define _LINKED_DEQUE_

typedef struct LinkedQueueNodeType
{
	void	*data;
	struct LinkedQueueNodeType* pLink;
} LinkedQueueNode;

typedef struct LinkedqueType
{
	int currentElementCount;	// ���� ������ ����
	LinkedQueueNode* pFrontNode;		// Front ����� ������
	LinkedQueueNode* pRearNode;		// Rear ����� ������
} LinkedQueue;

LinkedQueue* createLinkedQueue();
int isLinkedQueueEmpty(LinkedQueue* pLQueue);
int enqueueLQ(LinkedQueue* pLQueue, LinkedQueueNode *element);
LinkedQueueNode *dequeueLQ(LinkedQueue* pLQueue);
LinkedQueueNode *peekLQ(LinkedQueue* pLQueue);
void deleteLinkedQueue(LinkedQueue* pLQueue);
// LinkedQueueNode* copyLinkedQueueNode(LinkedQueueNode element);
LinkedQueue* copyLinkedQueue(LinkedQueue* pLQueue);
void    displayLQ(LinkedQueue* pLQueue);

#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_

#define TRUE		1
#define FALSE		0
#define ERROR		-1

#endif