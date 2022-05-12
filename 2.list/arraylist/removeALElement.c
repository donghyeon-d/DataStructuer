#include "arraylist.h"

int removeALElement(ArrayList* pList, int position)
{
    int i;

    i = pList->maxElementCount - 1;
    while (i > position)
    {
        pList->pElement[i - 1] = pList->pElement[i];
        i--;
    }
    pList->currentElementCount -= 1;
    return (1);
}