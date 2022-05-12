#include <unistd.h>
#include <stdlib.h>
#include "arraylist.h"

ArrayList* createArrayList(int maxElementCount)
{
    ArrayListNode element[maxElementCount];
    ArrayList *pList;

    pList = (ArrayList *)malloc(sizeof(ArrayList *));
    if (pList == NULL)
        return (NULL);
    pList->maxElementCount = maxElementCount;
    pList->currentElementCount = 0;
    pList->pElement = element;
    return (pList);
}


int isArrayListFull(ArrayList* pList)
{
    if (pList->currentElementCount == pList->maxElementCount)
        return (TRUE);
    else
        return (FALSE);
}

int addALElement(ArrayList* pList, int position, ArrayListNode element)
{
    int i;

    if (isArrayListFull(pList))
        return (FALSE);
    if (position < 0 || position > pList->currentElementCount)
        return (FALSE);
    i = pList->maxElementCount;
    while (i > position)
    {
        (pList->pElement)[i] = (pList->pElement)[i - 1];
        i--;
    }
    (pList->pElement)[position] = element;
    pList->currentElementCount++;;
    return (TRUE);
}

int removeALElement(ArrayList* pList, int position)
{
    int i;

    if (position < 0 || position >= pList->currentElementCount)
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

ArrayListNode* getALElement(ArrayList* pList, int position)
{
    return(&(pList->pElement[position]));
}

int getArrayListLength(ArrayList* pList)
{
    return (pList->currentElementCount);
}

void clearArrayList(ArrayList* pList)
{
    int i;

    i = 0;
    while (i < pList->currentElementCount)
    {
        pList->pElement[i].data = 0;
        i++;
    }
    pList->currentElementCount = 0;
}

void deleteArrayList(ArrayList* pList)
{
    free(pList->pElement);
    free (pList);
}

void displayArrayList(ArrayList* pList)
{
    write(1, pList->pElement, pList->currentElementCount);
}

