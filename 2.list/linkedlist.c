#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

LinkedList *createLinkedList()
{ 
    LinkedList *pLink;

    pLink = (LinkedList *)malloc(sizeof(LinkedList));
    if (pLink == NULL)
        return (NULL);
    pLink->currentElementCount = 0;
    pLink->headerNode.pLink = NULL;
    return (pLink);
} 

ListNode *getLLElement(LinkedList *pList, int position)
{ 
    ListNode *temp;
    int i;

    temp = &(pList->headerNode);
    i = -1;
    if (0 <= position && position < pList->currentElementCount)
    { 
        while (i < position)
        { 
            temp = temp->pLink;
            i++;
        } 
    }
    return (temp);
}

int addLLElement(LinkedList *pList, int position, ListNode element)
{ 
    ListNode *add;
    ListNode *temp;

    if (position < 0 && position > pList->currentElementCount)
    {
        return (FALSE);
    }
    add = (ListNode *)malloc(sizeof(ListNode));
    if (add == NULL)
        return (NULL);
    add->data = element.data;
    add->pLink = NULL;
    temp = getLLElement(pList, position - 1);
    add->pLink = temp->pLink;
    temp->pLink = add;
    pList->currentElementCount++;
    return (TRUE);
} 

int removeLLElement(LinkedList *pList, int position)
{
    ListNode *del;
    ListNode *temp;

    if (position < 0 && position > pList->currentElementCount - 1)
    {
        return (FALSE);
    }
    temp = getLLElement(pList, position - 1);
    del = getLLElement(pList, position);
    temp->pLink = del->pLink;
    free(del);
    pList->currentElementCount--;
    return (TRUE);
}

void clearLinkedList(LinkedList *pList)
{
    while (pList->currentElementCount > 0)
        removeLLElement(pList, pList->currentElementCount - 1);
}

void deleteLinkedList(LinkedList *pList)
{
    clearLinkedList(pList);
    free(pList);
}

int getLinkedListLength(LinkedList *pList)
{
    return (pList->currentElementCount);
}

void displayLinkedList(LinkedList *pList)
{
    ListNode *temp;
    int i;

    temp = pList->headerNode.pLink;
    i = 0;
    printf("Current Element Count : %d\n", pList->currentElementCount);
    printf("*---------------------------*\n");
    printf("|     node    |     data    |\n");
    printf("*---------------------------*\n");
    while (i < pList->currentElementCount)
    {
        printf("| %11d | %11d |\n", i, temp->data);
        temp = temp->pLink;
        i++;
    }
    printf("*---------------------------*\n");
}

int main()
{
    LinkedList *pList;
    ListNode node;

    pList = createLinkedList();
    for (int i = 0; i < 5; i++)
    {
        node.data = i;
        addLLElement(pList, i, node);
    }
    displayLinkedList(pList);
    removeLLElement(pList, 4);
    displayLinkedList(pList);
    clearLinkedList(pList);
    displayLinkedList(pList);
    node.data = 11;
    addLLElement(pList, 0, node);
    displayLinkedList(pList);
    node.data = 100;
    addLLElement(pList, 5, node);
    displayLinkedList(pList);
}