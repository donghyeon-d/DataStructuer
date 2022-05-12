#include "simulation.h"

//enqueue, SimCustomer만들기
void insertCutomer(int arrivalTime, int serviceTime, LinkedQueue *pQueue)
{
    LinkedQueueNode Node;

    if (pQueue == NULL)
        return ;
    Node.customer.arrivalTime = arrivalTime;
    Node.customer.serviceTime = serviceTime;
    Node.customer.status = arrival;
    Node.customer.startTime = -1;
    Node.customer.endTime = -1;
    Node.pLink = NULL;
    enqueueLQ(pQueue, &Node);
}

// pArrivalQueue == 고객목록, pWaitQueue 고객 도착시간 == 현재시간 됐을 때 추가해주기
void processArrival(int currentTime, LinkedQueue *pArrivalQueue, LinkedQueue *pWaitQueue)
{
    LinkedQueueNode *Node;

    if (pArrivalQueue == NULL || pWaitQueue == NULL)
        return ;
    while (pArrivalQueue->pFrontNode->customer.arrivalTime <= currentTime)
    {
        Node = dequeueLQ(pArrivalQueue);
        enqueueLQ(pWaitQueue, Node);
        free(Node);
        if (isLinkedQueueEmpty(pArrivalQueue))
            return ;
    }
}

// pWaitQueue에서 dequeue하고, SimCustomer멤버들 start로 바꿔주기
LinkedQueueNode* processServiceNodeStart(int currentTime, LinkedQueue *pWaitQueue)
{
    LinkedQueueNode *NodeStart;

    if (pWaitQueue == NULL || isLinkedQueueEmpty(pWaitQueue))
        return (NULL);
    NodeStart = dequeueLQ(pWaitQueue);
    NodeStart->customer.status = start;
    NodeStart->customer.startTime = currentTime;
    NodeStart->customer.endTime = NodeStart->customer.serviceTime + currentTime;
    return (NodeStart);
}

// SimCustomer멤버들 end로 바꿔주기, 사람 들어올때마다 pServiceUserCount++, pTotalWaitTime += startTime - arrivalTime
LinkedQueueNode* processServiceNodeEnd(int currentTime, LinkedQueueNode *pServiceNode, int *pServiceUserCount, int *pTotalWaitTime)
{
    LinkedQueueNode *pEndNode;

    if (pServiceNode == NULL)
        return (NULL);
    pEndNode = pServiceNode;
    if (pEndNode->customer.endTime == currentTime)
    {
        (*pServiceUserCount)++;
        (*pTotalWaitTime) += pEndNode->customer.startTime - pEndNode->customer.arrivalTime;
        pEndNode->customer.status = end;
        pServiceNode = NULL;
        return (pEndNode);
    }
    return (NULL);
}

// SimCustomer의 멤버들 보기좋게 출력해주기
void printSimCustomer(int currentTime, SimCustomer customer)
{
    char    *str;

    if (customer.status == arrival)
        str = "arrival";
    else if (customer.status == start)
        str = "start";
    else
        str = "end";
    printf("[CurrentTime : %d]\n", currentTime);
    printf("status : %s, arrivalTime : %d, serviceTime : %d, startTime : %d, endTime : %d\n", \
    str, customer.arrivalTime, customer.serviceTime, customer.startTime, customer.endTime);
}

// pWaitQueue 관련해서 보여줄것 출력해주기. 현재 대기인원, printSimCustomer
void printWaitQueueStatus(int currentTime, LinkedQueue *pWaitQueue)
{
    LinkedQueueNode *temp;
    int             n;

    if (pWaitQueue == NULL)
    {
        printf("pWaitQueue is NULL\n");
        return ;
    }
    temp = pWaitQueue->pFrontNode;
    if (temp == NULL)
    {
        printf("pWaitQueue is Empty!\n");
        return ;
    }
    n = 0;
    printf("Waiting Count : %d\n", pWaitQueue->currentElementCount);
    while (temp != NULL)
    {
        printf("Waiting index [%d]\n", n);
        printSimCustomer(currentTime, temp->customer);
        temp = temp->pLink;
        n++;
    }
}

// printWaitQueueStatus, serviceUserCount, totalWaitTime, 평균대기시간(float)
void printReport(LinkedQueue *pWaitQueue, int serviceUserCount, int totalWaitTime)
{
    if (pWaitQueue == NULL)
        return ;
    printf("Waiting Count : %d\n", pWaitQueue->currentElementCount);
    printf("serviceUserCount : %d\n", serviceUserCount);
    printf("totalWaitTime : %d\n", totalWaitTime);
    printf("average waiting time : %.2f\n", ((float)totalWaitTime / serviceUserCount));
}

int main()
{
    LinkedQueue     *pArrivalQueue;
    LinkedQueue     *pWaitQueue;
    LinkedQueueNode *pStartNode;
    LinkedQueueNode *pEndNode;
    int             serviceUserCount;
    int             totalWaitTime;
    int             currentTime;
    int             t;

    serviceUserCount = 0;
    totalWaitTime = 0;
    t = 0;
    pStartNode = NULL;
    pEndNode = NULL;
    pArrivalQueue = createLinkedQueue();
    pWaitQueue = createLinkedQueue();
    printf("CurrentTime : ");
    scanf("%d", &currentTime);
    insertCutomer(0, 3, pArrivalQueue);
    insertCutomer(2, 2, pArrivalQueue);
    insertCutomer(4, 1, pArrivalQueue);
    insertCutomer(6, 1, pArrivalQueue);
    insertCutomer(8, 3, pArrivalQueue);

    while (t <= currentTime)
    {
        if (!pArrivalQueue->currentElementCount && !pWaitQueue->currentElementCount)
            break ;
        processArrival(t, pArrivalQueue, pWaitQueue);
        if (pStartNode != NULL && pStartNode->customer.endTime == t)
        {
            pEndNode = processServiceNodeEnd(t, pStartNode, &serviceUserCount, &totalWaitTime);
            pStartNode = NULL;
        }
        if (pStartNode == NULL)
            pStartNode = processServiceNodeStart(t, pWaitQueue);
        printWaitQueueStatus(t, pWaitQueue);
        printf("\n\n");
        t++;
    }
    printReport(pWaitQueue, serviceUserCount, totalWaitTime);
}
