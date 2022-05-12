#include "linkedlist.h"

int addLLElement(LinkedList* pList, int position, ListNode element)
{
    int i;
    ListNode *temp;

    if (pList == NULL || position >= pList->currentElementCount)
        return (0);
    temp = &(pList->headerNode);
    i = 0;
    while (i < position - 1)
    {
        temp = temp->pLink;
        i++;
    }
    element.pLink = temp->pLink;
    temp->pLink = &element;
    pList->currentElementCount += 1;
    return (1);
}