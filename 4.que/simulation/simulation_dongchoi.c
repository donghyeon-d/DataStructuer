#include "simulation_dongchoi.h"

// 처음 온 손님 초기화해주고 도착 큐에 넣기
void    insertCustomer(int arrivalTime, int processTime, LinkedQueue *pQueue)
{
    LinkedQueueNode *customer;

    customer = malloc(sizeof(SimCustomer));
    if (customer == NULL)
        return ;
    customer->customer.status = arrival;
    customer->customer.arrivalTime = arrivalTime; // 도착시간
    customer->customer.serviceTime = processTime; // 서비스시간
    customer->customer.startTime = -1; // 시작시간
    customer->customer.endTime = -1; // startTime + serviceTime
    enqueueLQ(pQueue, customer);
    // free(customer);
}

// pArrivalQueue 는 앞으로 올 손님들 정보 다 들어가있는 큐
// 현재 시간 기준으로 대기줄 만들기
void processArrival(int currentTime, LinkedQueue *pArrivalQueue, LinkedQueue *pWaitQueue)
{
    LinkedQueueNode *temp;

    if (pArrivalQueue == NULL || pArrivalQueue->pFrontNode == NULL)
        return ;
    temp = peekLQ(pArrivalQueue);
    while (temp->customer.arrivalTime <= currentTime)
    {
        free(temp);
        temp = dequeueLQ(pArrivalQueue);
        if (temp == NULL)
            return ;
        temp->customer.status = arrival;
        enqueueLQ(pWaitQueue, temp);
        temp = peekLQ(pArrivalQueue);
        if (temp == NULL)
            break ;
    }
    free(temp);
}

LinkedQueueNode* processServiceNodeStart(int currentTime, LinkedQueue *pWaitQueue)
{
    LinkedQueueNode *serviceNode;

    if (pWaitQueue == NULL || pWaitQueue->pFrontNode == NULL)
        return (NULL);
    serviceNode = dequeueLQ(pWaitQueue);
    serviceNode->customer.startTime = currentTime;
    serviceNode->customer.status = start;
    serviceNode->customer.endTime = currentTime + serviceNode->customer.serviceTime;
    return (serviceNode);
}

LinkedQueueNode* processServiceNodeEnd(int currentTime, LinkedQueueNode *pServiceNode, int *pServiceUserCount, int *pTotalWaitTime)
{
    LinkedQueueNode *endNode;

    if (pServiceNode == NULL)// || pServiceNode->customer.startTime > currentTime)
        return (NULL);
    endNode = NULL;
    if (pServiceNode->customer.endTime == currentTime)
    {
        pServiceUserCount++;
        pTotalWaitTime += (pServiceNode->customer.startTime - pServiceNode->customer.arrivalTime);
        pServiceNode->customer.status = end;
        endNode = pServiceNode;
        pServiceNode = NULL;
    }
    return (endNode);
}

void printSimCustomer(int currentTime, SimCustomer customer)
{
    printf("currentTime : %d\n", currentTime);
    printf("status : %d\n", customer.status);
    printf("arrivalTime : %d\n", customer.arrivalTime);
    printf("serviceTime : %d\n", customer.serviceTime);
    printf("startTime : %d\n", customer.startTime);
    printf("endTime : %d\n", customer.endTime);
}

void printWaitQueueStatus(int currentTime, LinkedQueue *pWaitQueue)
{
    // 사람 수
    // 총 기다리고 있는 시간 합
    // 총 기다리고 있는 시간 평균
    LinkedQueueNode *waitNode;
    int customerCount;
    int totalWaitTime;
    int WaitAverageTime;

    customerCount = 0;
    totalWaitTime = 0;
    WaitAverageTime = 0;
    if (pWaitQueue == NULL || isLinkedQueueEmpty(pWaitQueue))
        return ;
    waitNode = peekLQ(pWaitQueue);
    while (waitNode)
    {
        customerCount++;
        totalWaitTime += currentTime - waitNode->customer.arrivalTime;
        WaitAverageTime = totalWaitTime / customerCount;
        waitNode = waitNode->pLink;
    }
    printf("currentTime : %d\n", currentTime);
    printf("customerCount : %d\n", customerCount);
    printf("totalWaitTime : %d\n", totalWaitTime);
    printf("WaitAverageTime : %d\n", WaitAverageTime);
}

void printReport(LinkedQueue *pWaitQueue, int serviceUserCount, int totalWaitTime, int currentTime)
{
    printf("<--- Current Wait Customer Status --->\n");
    printWaitQueueStatus(currentTime, pWaitQueue);
    printf("\n<--- Total Report --->\n");
    // printf()
}

int main()
{
    int currentTime; // 현재시간 
    int pServiceUserCount;
    int pTotalWaitTime;
    int n;
    LinkedQueue *pArrivalQueue; // 손님을 와있는 사람들 insertCustomer
    LinkedQueue *pWaitQueue; // 
    LinkedQueue *pEndQueue; // 
    LinkedQueueNode * serviceStartNode;
    LinkedQueueNode * serviceEndNode;


    pArrivalQueue = createLinkedQueue();
    pWaitQueue = createLinkedQueue();
    printf("input current Time : ");
    scanf("%d", &currentTime);
    if (currentTime < 0)
        printf("wrong current Time\n");
    pServiceUserCount = 0;
    pTotalWaitTime = 0;
    n = 0;
    serviceStartNode = NULL;
    serviceEndNode = NULL;

    insertCustomer(0, 3, pArrivalQueue);
    insertCustomer(2, 2, pArrivalQueue);
    insertCustomer(4, 1, pArrivalQueue);
    insertCustomer(6, 1, pArrivalQueue);
    insertCustomer(8, 3, pArrivalQueue);
    processArrival(currentTime, pArrivalQueue, pWaitQueue);

    printf("arrival\n");
    displayLQ(pArrivalQueue);
    printf("\nwait\n");
    displayLQ(pWaitQueue);

    while (n <= currentTime && !isLinkedQueueEmpty(pWaitQueue))
    {
        if (serviceStartNode == NULL)
            serviceStartNode = processServiceNodeStart(n, pWaitQueue);
        serviceEndNode = processServiceNodeEnd(n, serviceStartNode, &pServiceUserCount, &pTotalWaitTime);
        if (serviceEndNode != NULL)
        {
            enqueueLQ(pEndQueue, serviceEndNode);
            free(serviceStartNode);
            serviceStartNode = NULL;
        }
    // printf("\n<--- %d --->\n", n);
    // printf("arrival\n");
    // displayLQ(pArrivalQueue);
    // printf("wait\n");
    // displayLQ(pWaitQueue);
        n++;
    }
    // printReport(pWaitQueue, pServiceUserCount, pTotalWaitTime, currentTime);
    
    // system("leaks a.out");
}