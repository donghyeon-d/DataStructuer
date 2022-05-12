#include "linkedlist.h"

void deleteLinkedList(LinkedList* pList)
{
    clearLinkedList(pList);
    free(pList);
}