#include "arraylist.h"

int isArrayListFull(ArrayList* pList)
{
    int i;

    i = 0;
    while ((pList->pElement)[i] != '\0')
        i++;
    if (i == pList->maxElementCount)
        return (TRUE);
    else
        return (FALSE);
}

// 또는 //

int isArrayListFull(ArrayList* pList)
{
    if (pList->currentElementCount == pList->maxElementCount)
        return (TRUE);
    else
        return (FALSE);
}