#include <stdio.h>
#include <stdlib.h>
#include "bintraversal.h"
#include "linkedqueue.h"

static void	preorderTraversal(BinTreeNode *pNode)
{
	if (pNode == NULL)
		return ;
	printf("%c", pNode->data);
	pNode->visited = TRUE;
	preorderTraversal(getLeftChildNodeBT(pNode));
	preorderTraversal(getRightChildNodeBT(pNode));
}

void	preorderTraversalBinTree(BinTree *pBinTree)
{
	BinTreeNode	*root;

	if (pBinTree == NULL)
		return ;
	root = getRootNodeBT(pBinTree);
	preorderTraversal(root);	
}

static void	inorderTraversal(BinTreeNode *pNode)
{
	if (pNode == NULL)
		return ;
	inorderTraversal(getLeftChildNodeBT(pNode));
	printf("%c", pNode->data);
	pNode->visited = TRUE;
	inorderTraversal(getRightChildNodeBT(pNode));
}

void	inorderTraversalBinTree(BinTree *pBinTree)
{
	BinTreeNode	*root;

	if (pBinTree == NULL)
		return ;
	root = getRootNodeBT(pBinTree);
	inorderTraversal(root);
}

static void	postorderTraversal(BinTreeNode *pNode)
{
	if (pNode == NULL)
		return ;
	postorderTraversal(getLeftChildNodeBT(pNode));
	postorderTraversal(getRightChildNodeBT(pNode));
	printf("%c", pNode->data);
	pNode->visited = TRUE;
}

void	postorderTraversalBinTree(BinTree *pBinTree)
{
	BinTreeNode	*root;

	if (pBinTree == NULL)
		return ;
	root = getRootNodeBT(pBinTree);
	postorderTraversal(root);
}

void	levelOrderTraversalBinTree(BinTree *pBinTree)
{
	LinkedQueue		*queue;
	LinkedQueueNode	dummy;
	LinkedQueueNode	*temp;
	BinTreeNode		*curr;

	if (pBinTree == NULL)
		return ;
	curr = getRootNodeBT(pBinTree);
	if (curr == NULL)
		return ;
	queue = createLinkedQueue();
	dummy.data = curr;
	enqueueLQ(queue, &dummy);
	while (!isLinkedQueueEmpty(queue))
	{
		temp = dequeueLQ(queue);
		curr = (BinTreeNode *)(temp->data);
		printf("%c", curr->data);
		if (curr->pLeftChild != NULL)
		{
			dummy.data = curr->pLeftChild;
			enqueueLQ(queue, &dummy);
		}
		if (curr->pRightChild != NULL)
		{
			dummy.data = curr->pRightChild;
			enqueueLQ(queue, &dummy);
		}
		free(temp);
	}
}

int main(void)
{
	BinTree		*tree;
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
	tree = makeBinTree(dummy);
	dummy.data = 'B';
	pB = insertLeftChildNodeBT(getRootNodeBT(tree), dummy);
	dummy.data = 'C';
	pC = insertRightChildNodeBT(getRootNodeBT(tree), dummy);
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


	preorderTraversalBinTree(tree);
	printf("\n");
	inorderTraversalBinTree(tree);
	printf("\n");
	postorderTraversalBinTree(tree);
	printf("\n");
	levelOrderTraversalBinTree(tree);
	return (0);
}