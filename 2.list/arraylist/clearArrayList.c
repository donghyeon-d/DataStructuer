#include "arraylist.h"

void clearArrayList(ArrayList* pList)
{
    free(pList->pElement);
    free(pList);
}