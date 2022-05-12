#include "linkedlist.h"

LinkedList* createLinkedList()
{
    LinkedList *NewLinkedList;
    ListNode    headNode;

    NewLinkedList = (LinkedList *)malloc(sizeof(LinkedList *));
    if (NewLinkedList == NULL)
        return (NULL);
    NewLinkedList->currentElementCount = 0; // 헤더 노드는 미포함
    NewLinkedList->headerNode = headNode;
    return (NewLinkedList);
}