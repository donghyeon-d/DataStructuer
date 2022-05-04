#include "linkedlist.h"

int removeLLElement(LinkedList* pList, int position)
{
    int i;
    ListNode *temp;
    ListNode *del;

    if (pList == NULL || position >= pList->currentElementCount)
        return (0);
    temp = &(pList->headerNode);
    i = 0;
    while (i < position - 1)
    {
        temp = temp->pLink;
        i++;
    }
    del = temp->pLink;
    temp = temp->pLink->pLink;
    free(del);
    pList->currentElementCount -= 1;
    return (1);
}