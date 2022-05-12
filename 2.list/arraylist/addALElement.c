#include "arraylist.h"

int addALElement(ArrayList* pList, int position, ArrayListNode element)
{
    int i;

    if (isArrayListFull(pList))
        return (0);
    i = pList->maxElementCount - 1;
    while (i >= position)
    {
        (pList->pElement)[i] = (pList->pElement)[i - 1];
        i--;
    }
    (pList->pElement)[position] = element;
    pList->currentElementCount += 1;
    return (1);
}