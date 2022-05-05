#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"


LinkedQueueNode* processServiceNodeStart(int currentTime, LinkedQueue *pWaitQueue);
LinkedQueueNode* processServiceNodeEnd(int currentTime, LinkedQueueNode *pServiceNode, int *pServiceUserCount, int *pTotalWaitTime);
void printSimCustomer(int currentTime, SimCustomer customer);
void printWaitQueueStatus(int currentTime, LinkedQueue *pWaitQueue);
void printReport(LinkedQueue *pWaitQueue, int serviceUserCount, int totalWaitTime);

// 처음 온 손님 초기화해주고 도착 큐에 넣기
void    insertCustomer(int arrivalTime, int processTime, LinkedQueue *pQueue)
{
    LinkedQueueNode *customer;

    customer = malloc(sizeof(SimCustomer));
    if (customer == NULL)
        return (NULL);
    customer->customer.status = arrival;
    customer->customer.arrivalTime = arrivalTime; // 도착시간
    customer->customer.serviceTime = processTime; // 서비스시간
    customer->customer.startTime = -1; // 시작시간
    customer->customer.endTime = -1; // startTime + serviceTime
    enqueueLQ(pQueue, customer);
}

// 도착한 손님 때 되면 현재시간 넣고 대기줄에 넣기
void processArrival(int currentTime, LinkedQueue *pArrivalQueue, LinkedQueue *pWaitQueue);
{
    LinkedQueueNode *customer;

    customer = dequeueLQ(pArrivalQueue);
    customer->customer.startTime = currentTime;
    customer->customer.endTime = customer->customer.startTime + customer->customer.serviceTime;
    enqueueLQ(pWaitQueue, customer);
}

int main()
{
    int currentTime; // 현재시간 
    int serviceUserCount;
    int totalWaitTime;
    LinkedQueue *pArrivalQueue; // 손님을 와있는 사람들 insertCustomer
    LinkedQueue *pWaitQueue; // 
    

    pArrivalQueue = createLinkedQueue();
    pWaitQueue = createLinkedQueue();
    currentTime = 0;
    serviceUserCount = 0;
    totalWaitTime = 0;
    insertCustomer(0, 0, pArrivalQueue); // 원하는 만s큼 손님 넣기
    while (!isLinkedQueueEmpty(pArrivalQueue))
    {
        if (isLinkedQueueEmpty(pWaitQueue))
        {
            processArrival(currentTime, pArrivalQueue, pWaitQueue);
        }
        else
        {
            if (peekLQ(pWaitQueue)->customer.endTime == currentTime)
                free(dequeueLQ(pWaitQueue));
        }
        currentTime++;
    }
}