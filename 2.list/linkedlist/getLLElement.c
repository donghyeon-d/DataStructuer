#include "linkedlist.h"

ListNode* getLLElement(LinkedList* pList, int position)
{
    int i;
    ListNode *temp;

    if (pList == NULL || position >= pList->currentElementCount)
        return (NULL);
    temp = &(pList->headerNode);
    i = 0;
    while (i < position - 1)
    {
        temp = temp->pLink;
        i++;
    }
    return (temp);
}