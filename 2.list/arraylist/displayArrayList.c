#include "arraylist.h"

void displayArrayList(ArrayList* pList)
{
    write(1, pList->pElement, pList->currentElementCount);
}