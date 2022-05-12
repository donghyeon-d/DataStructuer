#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

LinkedList* createLinkedList()
{
    LinkedList *pLink;

    pLink = (LinkedList *)malloc(sizeof(LinkedList));
    if (pLink == NULL)
        return (NULL);
    pLink->currentElementCount = 0; // 헤더 노드는 미포함
    pLink->headerNode.pLink = NULL;
    return (pLink);
}

ListNode* getLLElement(LinkedList *pList, int position)
{
    int i;
    ListNode *temp;

    if (pList == NULL || position >= pList->currentElementCount)
        return (NULL);
    temp = &(pList->headerNode);
    i = -1;
    while (i < position)
    {
        temp = temp->pLink;
        i++;
    }
    return (temp);
}

int addLLElement(LinkedList *pList, int position, ListNode element)
{
    ListNode *temp;
    ListNode *add;

    add = (ListNode *)malloc(sizeof(ListNode));
    if (pList == NULL || position > pList->currentElementCount || add == NULL)
        return (FALSE);
    add->data = element.data;
    temp = getLLElement(pList, position - 1);
    if (temp != NULL)
        add->pLink = temp->pLink;
    temp->pLink = add;
    pList->currentElementCount++;
    return (1);
}

int removeLLElement(LinkedList *pList, int position)
{
    ListNode *temp;
    ListNode *del;

    if (pList == NULL || position >= pList->currentElementCount)
        return (FALSE);
    temp = getLLElement(pList, position - 1);
    del = temp->pLink;
    temp = del->pLink;
    free(del);
    pList->currentElementCount--;
    return (TRUE);
}


void clearLinkedList(LinkedList *pList)
{
    while (pList->currentElementCount > 0)
        removeLLElement(pList, pList->currentElementCount - 1);
}

int getLinkedListLength(LinkedList *pList)
{
    return (pList->currentElementCount);
}

void deleteLinkedList(LinkedList *pList)
{
    clearLinkedList(pList);
    free(pList);
}

void displayLinkedList(LinkedList *pList)
{
    ListNode *temp;
    int i;

    temp = &(pList->headerNode);
    i = 0;
    while (i < pList->currentElementCount)
    {
        temp = temp->pLink;
        printf("position[%d] : %d\n", i, temp->data);
        i++;
    }
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
    printf("\n\n");
    removeLLElement(pList, 4);
    displayLinkedList(pList);
    printf("\n\n");
    clearLinkedList(pList);
    
    displayLinkedList(pList);
    node.data = 11;
    addLLElement(pList, 0, node);
    displayLinkedList(pList);
    node.data = 100;
    addLLElement(pList, 5, node);
    displayLinkedList(pList);
}