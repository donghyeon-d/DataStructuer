#include "arraylist.h"

ArrayList* createArrayList(int maxElementCount)
{
    ArrayListNode element[maxElementCount];
    ArrayList *NewArrayList;

    NewArrayList = (ArrayList *)malloc(sizeof(ArrayList *));
    if (NewArrayList == NULL)
        return (NULL);
    NewArrayList->maxElementCount = maxElementCount;
    NewArrayList->currentElementCount = 0;
    NewArrayList->pElement = element;
}