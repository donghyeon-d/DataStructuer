#include <stdlib.h>
#include <stdio.h>
#include "polylist.h"

int addPolyNodeLast(PolyList* pList, int coef, int degree)
{
	PolyListNode *last;
	PolyListNode *node;

	last = getPLElement(pList, pList->currentElementCount - 1);
	node = (PolyListNode *)malloc(sizeof(PolyListNode));
	node->coef = coef;
	node->degree = degree;
	node->pLink = NULL;
	last->pLink = node;
	pList->currentElementCount++;
	return (TRUE);
}

PolyList* polyAdd(PolyList* pListA, PolyList* pListB)
{
	PolyList *ret;
	PolyListNode *nodeA;
	PolyListNode *nodeB;

	ret = createPolyList();
	nodeA = pListA->headerNode.pLink;
	nodeB = pListB->headerNode.pLink;
	while (nodeA != NULL && nodeB != NULL)
	{
		if (nodeA->degree == nodeB->degree)
		{
			addPolyNodeLast(ret, nodeA->coef + nodeB->coef, nodeA->degree);
			nodeA = nodeA->pLink;
			nodeB = nodeB->pLink;
		}
		else if (nodeA->degree > nodeB->degree)
		{
			addPolyNodeLast(ret, nodeA->coef, nodeA->degree);
			nodeA = nodeA->pLink;
		}
		else if (nodeA->degree < nodeB->degree)
		{
			addPolyNodeLast(ret, nodeB->coef, nodeB->degree);
			nodeB = nodeB->pLink;
		}
	}
	if (nodeA == NULL)
	{
		while (nodeB != NULL)
		{
			addPolyNodeLast(ret, nodeB->coef, nodeB->degree);
			nodeB = nodeB->pLink;
		}
	}
	else
	{
		while (nodeA != NULL)
		{
			addPolyNodeLast(ret, nodeA->coef, nodeA->degree);
			nodeA = nodeA->pLink;
		}
	}
	return (ret);
}

void displayPolyList(PolyList* pList)
{
	PolyListNode *temp;

	temp = pList->headerNode.pLink;
	while (temp != NULL)
	{
		printf("%dx%d ", temp->coef, temp->degree);
		temp = temp->pLink;
	}
	printf("\n");
}

PolyList *createPolyList()
{ 
    PolyList *pLink;

    pLink = (PolyList *)malloc(sizeof(PolyList));
    pLink->currentElementCount = 0;
    pLink->headerNode.pLink = NULL;
    return (pLink);
} 

PolyListNode *getPLElement(PolyList *pList, int position)
{ 
    PolyListNode *temp;
    int i;

    temp = &(pList->headerNode);
    i = -1;
    if (position >= 0 && position < pList->currentElementCount)
    { 
        while (i < position)
        { 
            temp = temp->pLink;
            i++;
        } 
    }
    return (temp);
}

int addPLElement(PolyList *pList, int position, PolyListNode element)
{ 
    PolyListNode *node;
    PolyListNode *temp;

    if (position < 0 && position > pList->currentElementCount)
    {
        return (FALSE);
    }
    node = (PolyListNode *)malloc(sizeof(PolyListNode));
    *node = element;
    node->pLink = NULL;
    temp = getPLElement(pList, position - 1);
    node->pLink = temp->pLink;
    temp->pLink = node;
    pList->currentElementCount++;
    return (TRUE);
} 
   
int removePLElement(PolyList *pList, int position)
{
    PolyListNode *del;
    PolyListNode *temp;

    if (position < 0 && position > pList->currentElementCount - 1)
    {
        return (FALSE);
    }
    temp = getPLElement(pList, position - 1);
    del = getPLElement(pList, position);
    temp->pLink = del->pLink;
    free(del);
    pList->currentElementCount--;
    return (TRUE);
}

void deletePolyList(PolyList *pList)
{
    clearPolyList(pList);
    free(pList);
}
  
void clearPolyList(PolyList *pList)
{
    while (pList->currentElementCount > 0)
        removePLElement(pList, pList->currentElementCount - 1);
}

int getPolyListLength(PolyList *pList)
{
    return (pList->currentElementCount);
}

int main()
{
    PolyList *pListA;
    PolyList *pListB;
	PolyList *add;

    pListA = createPolyList();
    pListB = createPolyList();
	addPolyNodeLast(pListA, 6, 6);
	addPolyNodeLast(pListA, 4, 5);
	addPolyNodeLast(pListA, 2, 2);
	addPolyNodeLast(pListB, 1, 5);
	addPolyNodeLast(pListB, 2, 4);
	addPolyNodeLast(pListB, 3, 2);
 	addPolyNodeLast(pListB, 4, 0);
 	displayPolyList(pListA);
  	displayPolyList(pListB);
	add = polyAdd(pListA, pListB);
	displayPolyList(add);
}