#include "linkedlist.h"

int getLinkedListLength(LinkedList* pList)
{
    int len;
    ListNode *temp;

    if (pList == NULL)
        return (NULL);
    temp = &(pList->headerNode);
    len = 0;
    while (temp == NULL)
    {
        temp = temp->pLink;
        len++;
    }
    len--;
    return (len);
}