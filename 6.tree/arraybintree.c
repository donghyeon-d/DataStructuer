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

int	isArrayBinTreeFull(ArrayBinTree *pbintree)
{
	if (pbintree == NULL || pbintree->pElement == NULL)
		return (-1);
	if (pbintree->maxElementCount == pbintree->currentElementCount)
		return (1);
	return (0);
}

int	isArrayBinTreeEmpty(ArrayBinTree *pbintree)
{
	if (pbintree == NULL || pbintree->pElement == NULL)
		return (-1);
	if (pbintree->currentElementCount == 0)
		return (1);
	return (0);
}

int insertLeftChildNodeABT(ArrayBinTree *bintree, int parentIndex, int data) // 부모 인덱스가 있는게 애매한듯
{
    int index;

    index = parentIndex * 2;
    if (bintree == NULL || parentIndex < 1 || index > bintree->maxElementCount || \
	bintree->maxElementCount == bintree->currentElementCount)
        return (-1);
	if (bintree->currentElementCount == 0)
		index = 1;
    bintree->pElement[index].data = data;
    bintree->currentElementCount++;
    return (index);
}

int insertRightChildNodeABT(ArrayBinTree *bintree, int rootIndex, int data)
{
    int index;

    index = rootIndex * 2 + 1;
    if (bintree == NULL || rootIndex < 0 || rootIndex > bintree->maxElementCount || \
	bintree->maxElementCount == bintree->currentElementCount)
        return (-1);
	if (bintree->currentElementCount == 0)
		index = 1;
    bintree->pElement[index].data = data;
    bintree->currentElementCount++;
    return (index);
}

int	insertInorder(ArrayBinTree	*bintree, int data)
{
    int index;

    if (bintree == NULL || bintree->pElement == NULL || bintree->maxElementCount == bintree->currentElementCount)
        return (-1);
    index = bintree->currentElementCount + 1;
    bintree->pElement[index].data = data;
    bintree->currentElementCount++;
	return (index);
}

int searchDataIndex(ArrayBinTree *bintree, int data)// O(n) 앞부터 쭉
{
    int index;

	if (bintree == NULL || bintree->pElement == NULL)
		return (-1);
    index = 0;
    while(++index <= bintree->currentElementCount)
    {
        if (bintree->pElement[index].data == data)
            return (index);
    }
    return (-1);
}

ArrayBinTreeNode *deleteArrayBinTree(ArrayBinTree *pbintree)
{
	ArrayBinTreeNode *temp;

	if (pbintree == NULL || pbintree->pElement == NULL || pbintree->currentElementCount == 0)
		return (NULL);
	temp = malloc(sizeof(ArrayBinTreeNode));
	if (temp == NULL)
		return (NULL);
	temp = &(pbintree->pElement)[pbintree->currentElementCount];
	pbintree->currentElementCount--;
	return (temp);
}

void    displayArrayBinTree(ArrayBinTree *bintree)
{
    int i;

    i = 0;
	if (bintree == NULL || bintree->pElement == NULL)
		return ;
    printf("    Max Element Count : %d\n", bintree->maxElementCount);
    printf("Current Element Count : %d\n", bintree->currentElementCount);
    while (++i <= bintree->currentElementCount)
        printf("| [%d] %d ", i, (bintree->pElement)[i].data);
    printf("|\n");
}

// int main()
// {
//     ArrayBinTree    *bintree;

//     bintree = makeArrayBinTree(5);
//     insertInorder(bintree, 'a');
//     insertInorder(bintree, 'b');
//     insertInorder(bintree, 'c');
//     insertInorder(bintree, 'd');
//     insertInorder(bintree, 'e');
//     displayArrayBinTree(bintree);
// }