#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int	insertMaxHeap(ArrayBinTree *pbintree, int data)
{
	int	index;
	ArrayBinTreeNode *pbintreeNode;

	if (pbintree == NULL || pbintree->pElement == NULL || isArrayBinTreeFull(pbintree))
		return (-1);
	pbintreeNode = pbintree->pElement;
	index = insertInorder(pbintree, data);
	while (index > 1 && data > pbintreeNode[index / 2].data)
	{
		pbintreeNode[index].data = pbintreeNode[index / 2].data;
		index /= 2;
	}
	pbintreeNode[index].data = data;
	return (1);
}

ArrayBinTreeNode	*deleteMaxHeap(ArrayBinTree *pbintree)
{
	ArrayBinTreeNode	*pbintreeNode;
	ArrayBinTreeNode	*pdelete;
	ArrayBinTreeNode	temp;
	int					parent;
	int					child;
	ArrayBinTreeNode	n;

	if (pbintree == NULL || pbintree->pElement == NULL || isArrayBinTreeEmpty(pbintree))
		return (NULL);
	parent = 1;
	pbintreeNode = pbintree->pElement;
	temp = pbintreeNode[parent];
	pbintreeNode[parent] = pbintreeNode[pbintree->currentElementCount];
	pbintreeNode[pbintree->currentElementCount] = temp;
	pdelete = deleteArrayBinTree(pbintree);
	n = pbintreeNode[parent];
	child = parent * 2;
	while (parent <= pbintree->currentElementCount / 2)
	{
		if (child < pbintree->currentElementCount && pbintreeNode[child].data < pbintreeNode[child + 1].data)
			child++;
		if (n.data >= pbintreeNode[child].data)
			break ;
		pbintreeNode[parent] = pbintreeNode[child];
		parent = child;
		child = parent * 2;
	}
	pbintreeNode[parent] = n;
	return (pdelete);
}
/*
<<<<<<< HEAD
int	insertMinHeap(ArrayBinTree *pbintree, int data)
{
	int	index;
	ArrayBinTreeNode *pbintreeNode;

	if (pbintree == NULL || pbintree->pElement == NULL || isArrayBinTreeFull(pbintree))
		return (-1);
	pbintreeNode = pbintree->pElement;
	index = insertInorder(pbintree, data);
	while (index > 1 && data < pbintreeNode[index / 2].data)
	{
		pbintreeNode[index].data = pbintreeNode[index / 2].data;
		index /= 2;
	}
	pbintreeNode[index].data = data;
	return (1);
}

ArrayBinTreeNode	*deleteMinHeap(ArrayBinTree *pbintree)
{
	ArrayBinTreeNode	*pbintreeNode;
	ArrayBinTreeNode	*pdelete;
	ArrayBinTreeNode	temp;
	int					parent;
	int					child;
	ArrayBinTreeNode	n;

	if (pbintree == NULL || pbintree->pElement == NULL || isArrayBinTreeEmpty(pbintree))
		return (NULL);
	parent = 1;
	pbintreeNode = pbintree->pElement;
	temp = pbintreeNode[parent];
	pbintreeNode[parent] = pbintreeNode[pbintree->currentElementCount];
	pbintreeNode[pbintree->currentElementCount] = temp;
	pdelete = deleteArrayBinTree(pbintree);
	n = pbintreeNode[parent];
	child = parent * 2;
	while (parent <= pbintree->currentElementCount / 2)
	{
		if (child < pbintree->currentElementCount && pbintreeNode[child].data > pbintreeNode[child + 1].data)
			child++;
		if (n.data <= pbintreeNode[child].data)
			break ;
		pbintreeNode[parent] = pbintreeNode[child];
		parent = child;
		child = parent * 2;
	}
	pbintreeNode[parent] = n;
	return (pdelete);
}

=======
>>>>>>> b173593f5676b37e1aa5e36aeeef49501d5f73a1
int main()
{
	ArrayBinTree *ptree;
	ArrayBinTreeNode *pnode;
	
	ptree = makeArrayBinTree(7);
	// insertMaxHeap(ptree, 1);
	// insertMaxHeap(ptree, 2);
	// insertMaxHeap(ptree, 3);
	// insertMaxHeap(ptree, 4);
	// insertMaxHeap(ptree, 5);
	// insertMaxHeap(ptree, 6);
	// insertMaxHeap(ptree, 7);

<<<<<<< HEAD
	insertMinHeap(ptree, 7);
	insertMinHeap(ptree, 6);
	insertMinHeap(ptree, 5);
	insertMinHeap(ptree, 4);
	insertMinHeap(ptree, 3);
	insertMinHeap(ptree, 2);
	insertMinHeap(ptree, 1);

	displayArrayBinTree(ptree);

	// pnode = deleteMaxHeap(ptree);
	pnode = deleteMinHeap(ptree);
	printf("delete : %d\n", pnode->data);
=======
	displayArrayBinTree(ptree);

	pnode = deleteMaxHeap(ptree);
	// printf("delete : %d\n", pnode->data);
>>>>>>> b173593f5676b37e1aa5e36aeeef49501d5f73a1
	displayArrayBinTree(ptree);
}
*/