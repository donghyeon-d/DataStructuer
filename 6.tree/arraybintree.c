#include <stdio.h>
#include <stdlib.h>
#include "arraybintree.h"

ArrayBinTree	*makeArrayBinTree(int maxElementCount)
{
    ArrayBinTree *bintree;

    bintree = malloc(sizeof(ArrayBinTree));
    if (bintree == NULL)
        return (NULL);
    bintree->pElement = malloc(sizeof(ArrayBinTreeNode) * maxElementCount + 1);
    if (bintree->pElement == NULL)
    {
        free(bintree);
        return (NULL);
    }
    bintree->maxElementCount = maxElementCount;
    bintree->currentElementCount = 0;
    return (bintree);
}

int insertLeftChildNodeABT(ArrayBinTree *bintree, int rootIndex, int data)
{
    int index;

    index = rootIndex * 2;
    if (bintree == NULL || rootIndex < 0 || rootIndex > bintree->maxElementCount || bintree->maxElementCount == bintree->currentElementCount || bintree->currentElementCount == 0)
        return (0);
    bintree->pElement[index].data = data;
    bintree->currentElementCount++;
    return (index);
}
int insertRightChildNodeABT(ArrayBinTree *bintree, int rootIndex, int data)
{
    int index;

    index = rootIndex * 2 + 1;
    if (bintree == NULL || rootIndex < 0 || rootIndex > bintree->maxElementCount || bintree->maxElementCount == bintree->currentElementCount || bintree->currentElementCount == 0)
        return (0);
    bintree->pElement[index].data = data;
    bintree->currentElementCount++;
    return (index);
}

void	insertInorder(ArrayBinTree	*bintree, int data)
{
    int index;

    if (bintree == NULL || bintree->maxElementCount == bintree->currentElementCount)
        return ;
    index = bintree->currentElementCount + 1;
    bintree->pElement[index].data = data;
    bintree->currentElementCount++;
}

int findDataIndex(ArrayBinTree	*bintree, int data)
{
    int index;

    index = 0;
    while(index < bintree->currentElementCount)
    {
        if (bintree->pElement[index].data == data)
            return (index);
    }
    return (0);
}

void    displayArrayBinTree(ArrayBinTree *bintree)
{
    int i;

    i = 1;
    printf("    Max Element Count : %d\n", bintree->maxElementCount);
    printf("Current Element Count : %d\n", bintree->currentElementCount);
    while (i <= bintree->currentElementCount)
    {
        printf("| [%d] %c ", i, bintree->pElement[i].data);
        i++;
    }
    printf("|\n");
}

int main()
{
    ArrayBinTree    *bintree;

    bintree = makeArrayBinTree(5);
    insertInorder(bintree, 'a');
    insertInorder(bintree, 'b');
    insertInorder(bintree, 'c');
    insertInorder(bintree, 'd');
    insertInorder(bintree, 'e');
    displayArrayBinTree(bintree);
}