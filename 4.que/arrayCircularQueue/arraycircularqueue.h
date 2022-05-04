#ifndef _ARRAY_QUEUE_
#define _ARRAY_QUEUE_

typedef struct ArrayCircularQueueNodeType
{
	char data;
} ArrayCircularQueueNode;

typedef struct ArrayCircularQueueType
{
	int maxElementCount;		// �ִ� ���� ����
	int currentElementCount;	// ���� ������ ����
	int front;					// front ��ġ
	int rear;					// rear ��ġ
	ArrayCircularQueueNode *pElement;	// ��� ������ ���� 1���� �迭 ������
} ArrayCircularQueue;

ArrayCircularQueue* createArrayCircularQueue(int maxElementCount);
int isArrayCircularQueueFull(ArrayCircularQueue* pACQueue);
int isArrayCircularQueueEmpty(ArrayCircularQueue* pACQueue);
int enqueueACQ(ArrayCircularQueue* pACQueue, ArrayCircularQueueNode element);
ArrayCircularQueueNode *dequeueACQ(ArrayCircularQueue* pACQueue);
ArrayCircularQueueNode *peekACQ(ArrayCircularQueue* pACQueue);
void deleteArrayCircularQueue(ArrayCircularQueue* pACQueue);
int canCircularEnqueueCount(ArrayCircularQueue* pACQueue);
void    displayACq(ArrayCircularQueue* pACQueue);


#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_

#define TRUE		1
#define FALSE		0
#define ERROR		0

#endif