#include "linkedlist.h"

void clearLinkedList(LinkedList* pList)
{
    ListNode *temp;
    ListNode *del;

    if (pList == NULL)
        return (0);
    temp = &(pList->headerNode);
    while (temp == NULL)
    {
        del = temp;
        temp = temp->pLink;
        free(del);
    }
}
