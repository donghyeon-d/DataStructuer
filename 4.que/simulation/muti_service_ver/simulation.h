
#ifndef _SIMULATION_
#define _SIMULATION_

#include <stdio.h>
#include <stdlib.h>

typedef enum SimStatusType 
{
    arrival,
    start,
    end
} SimStatus;

typedef struct SimCustomerType
{
    SimStatus   status;
    int         arrivalTime; // 도착시간
    int         serviceTime; // 서비스시간
    int         startTime; // 시간시간
    int         endTime; // 종료시각 : 시작시간 + 서비스시간
    // int         waitTime; // 현재시간 - 도착시간
} SimCustomer;

// typedef struct ArrayCircularQueueNodeType
// {
// 	char data;
// } ArrayCircularQueueNode;

typedef struct LinkedQueueNodeType
{
	SimCustomer customer;
	struct		LinkedQueueNodeType* pLink;
} LinkedQueueNode;

typedef struct LinkedqueType
{
	int currentElementCount;	// ���� ������ ����
	LinkedQueueNode* pFrontNode;		// Front ����� ������
	LinkedQueueNode* pRearNode;		// Rear ����� ������
} LinkedQueue;

typedef struct ArrayCircularQueueType
{
	int maxElementCount;		// �ִ� ���� ����
	int currentElementCount;	// ���� ������ ����
	int front;					// front ��ġ
	int rear;					// rear ��ġ
	LinkedQueueNode *pElement;	// ��� ������ ���� 1���� �迭 ������
} ArrayCircularQueue;


// Linked Queue
LinkedQueue* createLinkedQueue();
int isLinkedQueueEmpty(LinkedQueue* pLQueue);
int enqueueLQ(LinkedQueue* pLQueue, LinkedQueueNode *element);
LinkedQueueNode *dequeueLQ(LinkedQueue* pLQueue);
LinkedQueueNode *peekLQ(LinkedQueue* pLQueue);
void deleteLinkedQueue(LinkedQueue* pLQueue);
LinkedQueue* copyLinkedQueue(LinkedQueue* pLQueue);
void    displayLQ(LinkedQueue* pLQueue);


// Array Circular Queue
// Node 는 Linked 꺼 갖다 씀.
ArrayCircularQueue* createArrayCircularQueue(int maxElementCount);
int isArrayCircularQueueFull(ArrayCircularQueue* pACQueue);
int isArrayCircularQueueEmpty(ArrayCircularQueue* pACQueue);
int enqueueACQ(ArrayCircularQueue* pACQueue, LinkedQueueNode element);
LinkedQueueNode *dequeueACQ(ArrayCircularQueue* pACQueue);
LinkedQueueNode *peekACQ(ArrayCircularQueue* pACQueue);
void deleteArrayCircularQueue(ArrayCircularQueue* pACQueue);
int canCircularEnqueueCount(ArrayCircularQueue* pACQueue);
void    displayACq(ArrayCircularQueue* pACQueue);


// Simulation
void insertCutomer(int arrivalTime, int serviceTime, LinkedQueue *pQueue);
void processArrival(int currentTime, LinkedQueue *pArrivalQueue, LinkedQueue *pWaitQueue);
LinkedQueueNode* processServiceNodeStart(int currentTime, LinkedQueue *pWaitQueue);
LinkedQueueNode* processServiceNodeEnd(int currentTime, LinkedQueueNode *pServiceNode, int *pServiceUserCount, int *pTotalWaitTime);
void printSimCustomer(int currentTime, SimCustomer customer);
void printWaitQueueStatus(int currentTime, LinkedQueue *pWaitQueue);
void printReport(LinkedQueue *pWaitQueue, int serviceUserCount, int totalWaitTime);


#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_

#define TRUE		1
#define FALSE		0
#define ERROR		-1

#endif

