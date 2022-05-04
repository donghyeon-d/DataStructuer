#include <stdio.h>
#include <stdlib.h>
#include "circularlist.h"

CircularList* createCircularList()
{
    CircularList *pList;

    pList = (CircularList *)malloc(sizeof(CircularList));
    if (pList == NULL)
        return (NULL);
    pList->currentElementCount = 0;
    pList->headerNode.pLink = &(pList->headerNode);
    return (pList);
}

CircularNode createCircularNode(int data)
{
    CircularNode newNode;

    newNode.data = data;
    newNode.pLink = NULL;
    return(newNode);
}

CircularNode* getCLElement(CircularList* pList, int position)
{
    int i;
    CircularNode *temp;

    if (pList == NULL)
        return (NULL);
    i = -1;
    temp = &(pList->headerNode);
    if (position < 0)//
        return (temp);//
    if (position >= 0 && position < pList->currentElementCount)
    {
        while (i < position)
        {
            temp = temp->pLink;
            i++;
        }
    }
    return (temp);
}

int addCLElement(CircularList* pList, int position, CircularNode element)
{
    int i;
    CircularNode *temp;
    CircularNode *add;

    add = (CircularNode *)malloc(sizeof(CircularNode));
    if (pList == NULL || position < 0 || position > pList->currentElementCount || add == NULL)
        return (FALSE);
    i = 0;
    temp = getCLElement(pList, position - 1);
    add->data = element.data;
    add->pLink = temp->pLink;
    temp->pLink = add;
    pList->currentElementCount++;
    return (TRUE);
}

int removeCLElement(CircularList* pList, int position)
{
    int i;
    CircularNode *temp;
    CircularNode *del;

    if (pList == NULL || position < 0 || position >= pList->currentElementCount)
        return (FALSE);
    i = 0;
    temp = getCLElement(pList, position - 1);
    del = getCLElement(pList, position);//position == 0 && del == NULL 일떄, del->pRLink =?
    temp->pLink = del->pLink;
    free(del);
    pList->currentElementCount--;
    return (TRUE);
}

void clearCircularList(CircularList* pList)
{
    while (0 < pList->currentElementCount)
        removeCLElement(pList, pList->currentElementCount - 1);
}

int getCircularListLength(CircularList* pList)
{
    return (pList->currentElementCount);
}

void deleteCircularList(CircularList* pList)
{
    clearCircularList(pList);
    free(pList);
}

void displayCircularNode(CircularList* pList, int position)
{
    CircularNode *displayNode;

    if (pList == NULL)
        printf("List is NULL\n");
    else if (position < 0)
        printf("position is negative\n");
    if (pList == NULL || position < 0)
        return ;
    displayNode = getCLElement(pList, position);
    // printf("position[%d] | ", position);
    // if (position == 0)
    //     printf("L Header | ");
    printf("position[%d] | data %d | pLink %d\n", \
        position, displayNode->data, displayNode->pLink->data);
}

void displayCircularList(CircularList* pList)
{
    int i;

    if (pList == NULL)
    {
        printf("List is NULL\n");
        return ;
    }
    else if (pList->currentElementCount == 0)
    {
        printf("List have no element\n");
        return ;
    }
    i = 0;
    while (i < pList->currentElementCount)
    {
        displayCircularNode(pList, i);
        i++;
    }
    printf("len : %d\n", getCircularListLength(pList));
}

int main()
{
    CircularList *CL;
    CircularNode node;
    CircularNode *element;
    int i;
    
    CL = createCircularList();

    printf("\n\n*----- create test -----*\n");
    displayCircularList(CL);
    
    printf("\n\n*----- add test -----*\n");
    printf("*-- display each line --*\n");
    i = 0;
    while (i <= 4)
    {
        node = createCircularNode(i * 10);
        addCLElement(CL, i, node);
        printf("add position[%d]\n", i);
        displayCircularNode(CL, i);
        i++;
    }

    printf("\n\n*----- display test -----*\n");
    displayCircularList(CL);

    printf("\n\n*----- remove test -----*\n");
    printf("remove position[2]\n");
    removeCLElement(CL, 2);
    displayCircularList(CL);

    printf("\n\n*----- get element test -----*\n");
    i = 0;
    while(i < CL->currentElementCount)
    {
        element = getCLElement(CL, i);
        printf("element[%d] : %d\n", i, element->data);
        i++;
    }
    printf("(((compare)))\n");
    displayCircularList(CL);

    printf("\n\n*----- clear test -----*\n");
    clearCircularList(CL);
    displayCircularList(CL);

    printf("\n\n*----- delete test -----*\n");
    deleteCircularList(CL);
    CL = NULL;
    displayCircularList(CL);
    return (0);
}