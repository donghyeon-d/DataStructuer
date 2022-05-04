#include <stdio.h>
#include <stdlib.h>
#include "doublylist_choi.h"
// 헤드노드랑 0번쨰 노드 연결 ??
// 마지막 노드를 헤더노드랑 연결해줘야 함. (PDF 37페이지)

DoublyList* createDoublyList()
{
    DoublyList *pList;

    pList = (DoublyList *)malloc(sizeof(DoublyList));
    if (pList == NULL)
        return (NULL);
    pList->currentElementCount = 0;
    pList->headerNode.pLLink = NULL;
    pList->headerNode.pRLink = NULL;
    return (pList);
}

DoublyListNode createDoublyListNode(int data)
{
    DoublyListNode newNode;

    newNode.data = data;
    newNode.pRLink = NULL;
    newNode.pLLink = NULL;
    return(newNode);
}

DoublyListNode* getDLElement(DoublyList* pList, int position)//포지션이 반중에 어디냐에 따라서 왼쪽으로 돌지, 오른쪽으로 돌지 정해주기
{
    int i;
    DoublyListNode *temp;

    if (pList == NULL)
        return (NULL);
    i = -1;
    temp = &(pList->headerNode);
    if (position >= 0 && position < pList->currentElementCount)
    {
        while (i < position)
        {
            temp = temp->pRLink;
            i++;
        }
    }
    return (temp);
}

int addDLElement(DoublyList* pList, int position, DoublyListNode element)
{
    DoublyListNode *temp;
    DoublyListNode *add;

    if (pList == NULL || position < 0 || position > pList->currentElementCount)
        return (FALSE);
    add = (DoublyListNode *)malloc(sizeof(DoublyListNode));// null, 초기화 필요
    if (add == NULL)
        return (FALSE);
    *add = element;
    add->pLLink = NULL;
    add->pRLink = NULL;
    temp = getDLElement(pList, position - 1);
    add->pRLink = temp->pRLink;
    add->pLLink = temp;
    if (temp->pRLink != NULL)
        temp->pRLink->pLLink = add;
    temp->pRLink = add;
    if (position == 0)
    {

    }
    if (position == pList->currentElementCount)
    {
        add->pRLink = pList->headerNode;
        pList->headerNode.pLLink = add;
    }
    pList->currentElementCount++;
    return (TRUE);
}

int removeDLElement(DoublyList* pList, int position)
{
    int i;
    DoublyListNode *temp;
    DoublyListNode *del;

    if (pList == NULL || position < 0 || position >= pList->currentElementCount)
        return (FALSE);
    i = 0;
    temp = getDLElement(pList, position - 1);
    del = getDLElement(pList, position);
    temp->pRLink = del->pRLink;
    if (del->pRLink != NULL)
        del->pRLink->pLLink = temp;
    free(del);
    pList->currentElementCount--;
    return (TRUE);
}

void clearDoublyList(DoublyList* pList)
{
    while (0 < pList->currentElementCount)
        removeDLElement(pList, pList->currentElementCount - 1);
}

int getDoublyListLength(DoublyList* pList)
{
    return (pList->currentElementCount);
}

void deleteDoublyList(DoublyList* pList)
{
    clearDoublyList(pList);
    free(pList);
}

void displayDoublyListNode(DoublyList* pList, int position)
{
    DoublyListNode *displayNode;

    if (pList == NULL || position < 0)
    {
        if (pList == NULL)
            printf("List is NULL\n");
        else if (position < 0)
            printf("position is negative\n");
        return ;
    }
    displayNode = getDLElement(pList, position);
    if (position == 0 && displayNode->pRLink == NULL)
    {
        printf("position[%d] | L Header | data %d | R NULL\n", \
        position, displayNode->data);
    }
    else if (position == 0 && displayNode->pRLink != NULL)
    {
        printf("position[%d] | L Header | data %d | Rdata %d\n", \
        position, displayNode->data, displayNode->pRLink->data);
    }
    else if (position != 0 && displayNode->pRLink == NULL)
    {
        printf("position[%d] | Ldata %d | data %d | R NULL\n", \
        position, displayNode->pLLink->data, displayNode->data);
    }
    else
    {
        printf("position[%d] | Ldata %d | data %d | Rdata %d\n", \
        position, displayNode->pLLink->data, displayNode->data, displayNode->pRLink->data);
    }
}

void displayDoublyList(DoublyList* pList)
{
    int i;

    if (pList == NULL)
    {
        printf("List is NULL\n");
        return ;
    }
    else if (pList->headerNode.pRLink == NULL)
    {
        printf("List have no element\n");
        return ;
    }
    i = 0;
    while (i < pList->currentElementCount)
    {
        displayDoublyListNode(pList, i);
        i++;
    }
    printf("len : %d\n", getDoublyListLength(pList));
}


int main()
{
    DoublyList *DL;
    DoublyListNode node;
    DoublyListNode *element;
    int i;
    
    DL = createDoublyList();

    printf("\n\n*----- create test -----*\n");
    displayDoublyList(DL);
    
    printf("\n\n*----- add test -----*\n");
    printf("*-- display each line --*\n");
    i = 0;
    while (i <= 4)
    {
        node = createDoublyListNode(i * 10);
        addDLElement(DL, i, node);
        printf("add position[%d]\n", i);
        displayDoublyListNode(DL, i);
        i++;
    }

    printf("\n\n*----- display test -----*\n");
    displayDoublyList(DL);

    printf("\n\n*----- remove test -----*\n");
    printf("remove position[2]\n");
    removeDLElement(DL, 2);
    displayDoublyList(DL);

    printf("\n\n*----- get element test -----*\n");
    i = 0;
    while(i < DL->currentElementCount)
    {
        element = getDLElement(DL, i);
        printf("element[%d] : %d\n", i, element->data);
        i++;
    }

    printf("\n\n*----- clear test -----*\n");
    clearDoublyList(DL);
    displayDoublyList(DL);

    printf("\n\n*----- delete test -----*\n");
    deleteDoublyList(DL);
    DL = NULL;
    displayDoublyList(DL);
    return (0);
}