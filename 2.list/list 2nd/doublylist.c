#include <stdlib.h>
#include <stdio.h>
#include "doublylist.h"

DoublyList *createDoublyList()
{ 
    DoublyList *pLink;

    pLink = (DoublyList *)malloc(sizeof(DoublyList));
    pLink->currentElementCount = 0;
    pLink->headerNode.pLLink = NULL;
    pLink->headerNode.pRLink = NULL;
    return (pLink);
} 

DoublyListNode *getDLElement(DoublyList *pList, int position)
{ 
    DoublyListNode *temp;
    int i;

    temp = &(pList->headerNode);
    i = -1;
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

int addDLElement(DoublyList *pList, int position, DoublyListNode element)
{ 
    DoublyListNode *node;
    DoublyListNode *temp;

    if (position < 0 && position > pList->currentElementCount)
    {
        return (FALSE);
    }
    node = (DoublyListNode *)malloc(sizeof(DoublyListNode));
    *node = element;
    node->pLLink = NULL;
    node->pRLink = NULL;
    temp = getDLElement(pList, position - 1);
    if (pList->currentElementCount == 0 || pList->currentElementCount == position)
    {
        temp->pRLink = node;
        node->pLLink = temp;
    }
    else
    {
        temp->pRLink->pLLink = node;
        node->pRLink = temp->pRLink;
        temp->pRLink = node;
        node->pLLink = temp;
    }
    pList->currentElementCount++;
    return (TRUE);
} 

int removeDLElement(DoublyList *pList, int position)
{
    DoublyListNode *del;
    DoublyListNode *temp;

    if (position < 0 && position > pList->currentElementCount - 1)
    {
        return (FALSE);
    }
    temp = getDLElement(pList, position - 1);
    del = getDLElement(pList, position);
    if (pList->currentElementCount == 1 || pList->currentElementCount == position + 1)
    {
        temp->pRLink = NULL;
    }
    else
    {
        del->pRLink->pLLink = temp;
        temp->pRLink = del->pRLink;
    }
    free(del);
    pList->currentElementCount--;
    return (TRUE);
}

void deleteDoublyList(DoublyList *pList)
{
    clearDoublyList(pList);
    free(pList);
}
  
void clearDoublyList(DoublyList *pList)
{
    while (pList->currentElementCount > 0)
        removeDLElement(pList, pList->currentElementCount - 1);
}

int getDoublyListLength(DoublyList *pList)
{
    return (pList->currentElementCount);
}

void displayDoublyList(DoublyList *pList)
{
    DoublyListNode *temp;
    int i;

    temp = pList->headerNode.pRLink;
    i = 0;
    printf("Current Element Count : %d\n", pList->currentElementCount);
    printf("*---------------------------*\n");
    printf("|     node    |     data    |\n");
    printf("*---------------------------*\n");
    while (i < pList->currentElementCount)
    {
        printf("| %11d | %11d |\n", i, temp->data);
        temp = temp->pRLink;
        i++;
    }
    printf("*---------------------------*\n");
}

int main()
{
    DoublyList *pList;
    DoublyListNode node;

    pList = createDoublyList();
    for (int i = 0; i < 5; i++)
    {
        node.data = i;
        addDLElement(pList, i, node);
    }
    displayDoublyList(pList);
    removeDLElement(pList, 4);
    displayDoublyList(pList);
    clearDoublyList(pList);
    displayDoublyList(pList);
    node.data = 11;
    addDLElement(pList, 0, node);
    displayDoublyList(pList);
    node.data = 100;
    addDLElement(pList, 5, node);
    displayDoublyList(pList);
}