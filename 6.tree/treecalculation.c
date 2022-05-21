#include <stdio.h>
#include <stdlib.h>
#include "arraybintree.h"
#include "bintree.h"
#include "treecalculation.h"
#include "bintraversal.h"

// array binary tree duplicate. expand maxElementCount
ArrayBinTree	*dupleArrayBinTree(ArrayBinTree *pbintree, int maxElementCount)
{
    ArrayBinTree *newbintree;
    int i;

    newbintree = malloc(sizeof(ArrayBinTree));
    if (newbintree == NULL)
        return (NULL);
    newbintree->pElement = malloc(sizeof(ArrayBinTreeNode) * maxElementCount + 1);
    if (newbintree->pElement == NULL)
    {
        free(newbintree);
        return (NULL);
    }
    newbintree->maxElementCount = maxElementCount;
    newbintree->currentElementCount = pbintree->currentElementCount;
    i = 0;
    while (i++ <= newbintree->currentElementCount)
        (newbintree->pElement)[i] = (pbintree->pElement)[i];
    return (newbintree);
}

// binary tree duplicate 
static BinTreeNode *copyTreeUtil(BinTreeNode *pNode)
{
    BinTreeNode *temp;

    if (pNode == NULL)
        return (NULL);
    temp = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    temp->data = pNode->data;
    temp->pLeftChild = copyTreeUtil(pNode->pLeftChild);
    temp->pRightChild = copyTreeUtil(pNode->pRightChild);
    return (temp);
}

BinTree	*copyBinTree(BinTree *pbintree)
{
    BinTree *newbintree;

    if (pbintree == NULL)
        return (NULL);
    newbintree = malloc(sizeof(BinTree));
    if (newbintree == NULL)
        return (NULL);
    newbintree->pRootNode = copyTreeUtil(pbintree->pRootNode);
    return (newbintree);
}

// binary tree is equal
static int	isEqualBintreeUtil(BinTreeNode *pNodeA, BinTreeNode *pNodeB)
{
    int isequal;

	if (pNodeA == NULL && pNodeB == NULL)
		return (TRUE);
	if (pNodeA->data != pNodeB->data)
        return (FALSE);
	if (!(isEqualBintreeUtil(getLeftChildNodeBT(pNodeA), getLeftChildNodeBT(pNodeB))))
        return (FALSE);
    if (!(isEqualBintreeUtil(getRightChildNodeBT(pNodeA), getRightChildNodeBT(pNodeB))))
        return (FALSE);
    return (TRUE);
}

int	isEqualBintree(BinTree *pBinTreeA, BinTree *pBinTreeB)
{
	BinTreeNode	*rootA;
    BinTreeNode	*rootB;

	if (pBinTreeA == NULL || pBinTreeB == NULL)
		return (FALSE);
	rootA = getRootNodeBT(pBinTreeA);
    rootB = getRootNodeBT(pBinTreeB);
    if (pBinTreeA == NULL || pBinTreeB == NULL || rootA == NULL ||  rootB == NULL)
        return (FALSE);
	if (isEqualBintreeUtil(rootA, rootB))
        return (TRUE);
    return (FALSE);
}

// binary tree count Node
static int countBintreeUtil(BinTreeNode *pBinTreeNode, int *count)
{
    if (pBinTreeNode == NULL)
        return (*count);
    countBintreeUtil(pBinTreeNode->pLeftChild, count);
    countBintreeUtil(pBinTreeNode->pRightChild, count);
    (*count)++;
    return (*count);
}

int countBintree(BinTree *pBinTree)
{
    int count;

    if (pBinTree == NULL)
        return (0);
    count = 0;
    count = countBintreeUtil(pBinTree->pRootNode, &count);
    return (count);
}

// binary tree count leafs
static int countBintreeLeafNodeUtil(BinTreeNode *pBinTreeNode, int *count)
{
    if (pBinTreeNode->pLeftChild == NULL && pBinTreeNode->pRightChild == NULL)
    {
        (*count)++;
        return (*count);
    }
    if (pBinTreeNode->pLeftChild != NULL)
        countBintreeLeafNodeUtil(pBinTreeNode->pLeftChild, count);
    if (pBinTreeNode->pRightChild != NULL)
    countBintreeLeafNodeUtil(pBinTreeNode->pRightChild, count);
    return (*count);
}

int countBintreeLeafNode(BinTree *pBinTree)
{
    int count;

    if (pBinTree == NULL || pBinTree->pRootNode == NULL)
        return (0);
    count = 0;
    count = countBintreeLeafNodeUtil(pBinTree->pRootNode, &count);
    return (count);
}

int main()
{
    BinTree		*treeA;
    BinTree		*treeB;
	BinTreeNode	dummy;
	BinTreeNode *pA;
	BinTreeNode *pB;
	BinTreeNode *pC;
	BinTreeNode *pD;
	BinTreeNode *pE;
	BinTreeNode *pF;
	BinTreeNode *pG;
	BinTreeNode *pH;
	BinTreeNode *pI;
	BinTreeNode *pJ;
	BinTreeNode *pK;
	BinTreeNode *pL;
	BinTreeNode *pM;
	
	dummy.data = 'A';
	dummy.visited = FALSE;
	dummy.pLeftChild = NULL;
	dummy.pRightChild = NULL;
	treeA = makeBinTree(dummy);
	dummy.data = 'B';
	pB = insertLeftChildNodeBT(getRootNodeBT(treeA), dummy);
	dummy.data = 'C';
	pC = insertRightChildNodeBT(getRootNodeBT(treeA), dummy);
	dummy.data = 'D';
	pD = insertLeftChildNodeBT(pB, dummy);
	dummy.data = 'E';
	pE = insertRightChildNodeBT(pB, dummy);
	dummy.data = 'F';
	pF = insertLeftChildNodeBT(pC, dummy);
	dummy.data = 'G';
	pG = insertRightChildNodeBT(pC, dummy);
	dummy.data = 'H';
	pH = insertLeftChildNodeBT(pD, dummy);
	dummy.data = 'I';
	pI = insertRightChildNodeBT(pD, dummy);
	dummy.data = 'J';
	pJ = insertLeftChildNodeBT(pE, dummy);
	dummy.data = 'K';
	pK = insertRightChildNodeBT(pF, dummy);
	dummy.data = 'L';
	pL = insertLeftChildNodeBT(pG, dummy);
	dummy.data = 'M';
	pM = insertRightChildNodeBT(pG, dummy);
    
    treeB = copyBinTree(treeA);

    printf("--------\nA\n");
    preorderTraversalBinTree(treeA);
    printf("--------\nB\n");
    preorderTraversalBinTree(treeB);
    printf("\nprint\n%c, %c, %c\n", treeB->pRootNode->data, treeB->pRootNode->pLeftChild->data,treeB->pRootNode->pRightChild->data);

    int e = isEqualBintree(treeA, treeB);
    int ca = countBintree(treeA);
    int cb = countBintree(treeB);
    printf("equal : %d\n", e);
    printf("count A : %d\n", ca);
    printf("count B : %d\n", cb);

    printf("leaf node count : %d\n", countBintreeLeafNode(treeA));
}