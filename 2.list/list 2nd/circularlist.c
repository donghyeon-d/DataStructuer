#include <stdlib.h>
#include <stdio.h>
#include "circularlist.h"

CircularList *createCircularList()
{ 
    CircularList *pLink;

    pLink = (CircularList *)malloc(sizeof(CircularList));
    pLink->currentElementCount = 0;
    pLink->headerNode.pLink = NULL;
    return (pLink);
} 

CircularListNode *getCLElement(CircularList *pList, int position)
{ 
    CircularListNode *temp;
    int i;

    temp = &(pList->headerNode);
    i = -1;
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

int addCLElement(CircularList *pList, int position, CircularListNode element)
{ 
    CircularListNode *node;
    CircularListNode *temp;

    if (position < 0 && position > pList->currentElementCount)
    {
        return (FALSE);
    }
    node = (CircularListNode *)malloc(sizeof(CircularListNode ));
    *node = element;
    node->pLink = NULL;
    temp = getCLElement(pList, position - 1);
    node->pLink = temp->pLink;
    temp->pLink = node;
    if (position == pList->currentElementCount)
    {
        temp = getCLElement(pList, 0);
        node->pLink = temp;
    }
    pList->currentElementCount++;
    return (TRUE);
}

int removeCLElement(CircularList *pList, int position)
{
    CircularListNode *del;
    CircularListNode *temp;

    if (position < 0 || position > pList->currentElementCount - 1)
    {
        return (FALSE);
    }
    temp = getCLElement(pList, position - 1);
    del = getCLElement(pList, position);
    temp->pLink = del->pLink;
    free(del);
    pList->currentElementCount--;
    return (TRUE);
}

void deleteCircularList(CircularList *pList)
{
    clearCircularList(pList);
    free(pList);
}


void clearCircularList(CircularList *pList)
{
    while (pList->currentElementCount > 0)
        removeCLElement(pList, pList->currentElementCount - 1);
}

int getCircularListLength(CircularList *pList)
{
    return (pList->currentElementCount);
}

void displayCircularList(CircularList *pList)
{
    CircularListNode *temp;
    int i;

    temp = pList->headerNode.pLink;
    i = 0;
    printf("Current Element Count : %d\n", pList->currentElementCount);
    printf("*---------------------------*\n");
    printf("|     node    |     data    |\n");
    printf("*---------------------------*\n");
    while (i < pList->currentElementCount * 2)
    {
        printf("| %11d | %11d |\n", i, temp->data);
        temp = temp->pLink;
        i++;
    }
    printf("*---------------------------*\n");
}

int main()
{
    CircularList *pList;
    CircularListNode node;

    pList = createCircularList();
    for (int i = 0; i < 5; i++)
    {
        node.data = i;
        addCLElement(pList, i, node);
    }
    displayCircularList(pList);
    removeCLElement(pList, 4);
    displayCircularList(pList);
    clearCircularList(pList);
    displayCircularList(pList);
    /*node.data = 11;
    addCLElement(pList, 0, node);
    displayCircularList(pList);
    node.data = 100;
    addCLElement(pList, 5, node);
    displayCircularList(pList);*/
}