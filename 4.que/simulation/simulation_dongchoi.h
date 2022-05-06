

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
} SimCustomer;

typedef struct LinkedQueueNodeType
{
	SimCustomer	customer;
	struct		LinkedQueueNodeType* pLink;
} LinkedQueueNode;

typedef struct LinkedqueType
{
	int currentElementCount;	// ���� ������ ����
	LinkedQueueNode* pFrontNode;		// Front ����� ������
	LinkedQueueNode* pRearNode;		// Rear ����� ������
} LinkedQueue;

// 고객 도착(고객 목록 큐) creat customer
void insertCutomer(int arrivalTime, int processTime, LinkedQueue *pQueue);

// 현재 시간 기준으로 대기줄 만들기
void processArrival(int currentTime, LinkedQueue *pArrivalQueue, LinkedQueue *pWaitQueue);
LinkedQueueNode* processServiceNodeStart(int currentTime, LinkedQueue *pWaitQueue);
LinkedQueueNode* processServiceNodeEnd(int currentTime, LinkedQueueNode *pServiceNode, int *pServiceUserCount, int *pTotalWaitTime);
void printSimCustomer(int currentTime, SimCustomer customer);
void printWaitQueueStatus(int currentTime, LinkedQueue *pWaitQueue);
void printReport(LinkedQueue *pWaitQueue, int serviceUserCount, int totalWaitTime, int currentTime);



LinkedQueue* createLinkedQueue();
int isLinkedQueueEmpty(LinkedQueue* pLQueue);
int enqueueLQ(LinkedQueue* pLQueue, LinkedQueueNode *element);
LinkedQueueNode *dequeueLQ(LinkedQueue* pLQueue);
LinkedQueueNode *peekLQ(LinkedQueue* pLQueue);
void deleteLinkedQueue(LinkedQueue* pLQueue);
// LinkedQueueNode* copyLinkedQueueNode(LinkedQueueNode element);
LinkedQueue* copyLinkedQueue(LinkedQueue* pLQueue);
void    displayLQ(LinkedQueue* pLQueue);


#define TRUE		1
#define FALSE		0
#define ERROR		-1
