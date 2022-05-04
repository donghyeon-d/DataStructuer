#include <stdlib.h>
#include <stdio.h>
#include "arraylist.h"

ArrayList *createArrayList(int maxElementCount)
{
    ArrayList *pList;

    pList = (ArrayList *)malloc(sizeof(ArrayList));
    if (pList == NULL)
        return (NULL);
    pList->maxElementCount = maxElementCount;
    pList->currentElementCount = 0;
    pList->pElement = (ArrayListNode *)malloc(sizeof(ArrayListNode) * maxElementCount);
    if (pList->pElement == NULL)
        return (NULL);
	return (pList);
}

int isArrayListFull(ArrayList *pList)
{
    if (pList->currentElementCount == pList->maxElementCount)
        return (TRUE);
    return (FALSE);
}

int addALElement(ArrayList *pList, int position, ArrayListNode element)
{
    int i;

    if (isArrayListFull(pList))
        return (FALSE);
    if (position < 0 && position > pList->currentElementCount)
        return (FALSE);
    i = pList->currentElementCount;
    while (i > position)
    {
        pList->pElement[i] = pList->pElement[i - 1];
        i--;
    }
    pList->pElement[position] = element;
    pList->currentElementCount++;
    return (TRUE);
}

int removeALElement(ArrayList *pList, int position)
{
    int i;

    if (position < 0 && position >= pList->currentElementCount)
        return (FALSE);
    i = position;
    while (i < pList->currentElementCount)
    {
        pList->pElement[i] = pList->pElement[i + 1];
        i++;
    }
    pList->currentElementCount--;
    return (TRUE);
}

ArrayListNode *getALElement(ArrayList *pList, int position)
{
    ArrayListNode *temp;

    temp = NULL;
    temp = &(pList->pElement[position]);
    return (temp);
}

int getArrayListLength(ArrayList *pList)
{
    return (pList->currentElementCount);
}

void clearArrayList(ArrayList *pList)
{
    free(pList->pElement);
    pList->pElement = NULL;
}

void deleteArrayList(ArrayList *pList)
{
    clearArrayList(pList);
    free(pList);
}

void displayArrayList(ArrayList *pList)
{
    int i;

    i = 0;
    printf("    Max Element Count : %d\n", pList->maxElementCount);
    printf("Current Element Count : %d\n", pList->currentElementCount);
    printf("*---------------------------*\n");
    printf("|    index    |     data    |\n");
    printf("*---------------------------*\n");
    while (i < pList->currentElementCount)
    {
        printf("| %11d | %11d |\n", i, pList->pElement[i].data);
        i++;
    }
    printf("*---------------------------*\n");
}

int main()
{
	ArrayList *pList;
	ArrayListNode node;

	pList = createArrayList(19);
	for (int i = 0; i < 5; i++)
	{
		node.data = i * 1000000000;	
		addALElement(pList, i, node);
	}
	displayArrayList(pList);
	removeALElement(pList, 2);
	//ArrayListNode *pNode = getALElement(pList, 3);
	addALElement(pList, 0, node);
	//clearArrayList(pList);
	displayArrayList(pList);
	deleteArrayList(pList);
}

