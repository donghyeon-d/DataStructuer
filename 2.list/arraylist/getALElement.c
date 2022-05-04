#include "arraylist.h"

ArrayListNode* getALElement(ArrayList* pList, int position)
{
    return(&(pList->pElement[position]));
}