#include "linkedqueue.h"

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


// 고객 도착(고객 목록 큐) creat customer
void insertCutomer(int arrivalTime, int processTime, LinkedQueue *pQueue);

// 
void processArrival(int currentTime, LinkedQueue *pArrivalQueue, LinkedQueue *pWaitQueue); // 도착한 사람들에서 
LinkedQueueNode* processServiceNodeStart(int currentTime, LinkedQueue *pWaitQueue);
LinkedQueueNode* processServiceNodeEnd(int currentTime, LinkedQueueNode *pServiceNode, int *pServiceUserCount, int *pTotalWaitTime);
void printSimCustomer(int currentTime, SimCustomer customer);
void printWaitQueueStatus(int currentTime, LinkedQueue *pWaitQueue);
void printReport(LinkedQueue *pWaitQueue, int serviceUserCount, int totalWaitTime);