#include <stdlib.h>
#include <stdio.h>
#include "bintree.h"

BinTree *makeBinTree(BinTreeNode rootNode)
{
    BinTree *newTree;

    newTree = malloc(sizeof(BinTree));
    if (bintree == NULL)
        return (NULL);
	newTree->pRootNode = malloc(sizeof(BinTreeNode));
    if (newTree->pRootNode == NULL)
    {
        free(newTree);
        return (NULL);
    }
    *(newTree->pRootNode) = rootNode;
    return (newTree);
}

BinTreeNode *getRootNodeBT(BinTree* pBinTree)
{
    BinTreeNode *rootNode;
    if (pBinTree == NULL)
        return (NULL);
    rootNode = malloc(sizeof(BinTreeNode));
    if (rootNode == NULL)
        return (NULL);
	*rootNode = *(pBinTree->RootNdoe);
    return (rootNode);
}

BinTreeNode *insertLeftChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    BinTreeNode *LeftChildNode;
    
    if (pParentNode == NULL|| pParentNode->pLeftChild == NULL) 
        return (NULL);
    LeftChildNode = malloc(sizeof(BinTreeNode));
    if (LeftChildNode == NULL)
        return (NULL);
	*LeftChildNode = element;
    pParentNode->pLeftChild = LeftChildNode;
    return (LeftChildNode);
}

BinTreeNode* insertRightChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    BinTreeNode *rightChildNode;
    
    if (pParentNode == NULL || pParentNode->pRightChild == NULL)
        return (NULL);
    rightChildNode = malloc(sizeof(BinTreeNode));
    if (rightChildNode == NULL)
        return (NULL);
	*rightChildNode = element;
    pParentNode->pRightChild = rightChildNode;
    return (rightChildNode);
}

BinTreeNode* getLeftChildNodeBT(BinTreeNode* pNode)
{
    BinTreeNode *LeftChildNode;

    if (pNode == NULL || pNode->pLeftChild == NULL)
        return (NULL);
    LeftChildNode = malloc(sizeof(BinTreeNode));
    if (LeftChildNode == NULL)
        return (NULL);
	*LeftChildNode = *(pNode->pLeftChild);
	return (LeftChildNode);
}

BinTreeNode *peekRootNodeBT(BinTree* pBinTree)
{
    BinTreeNode *rootNode;
    if (pBinTree == NULL || pBinTree->RootNdoe)
        return (NULL);
    *rootNode = *(pBinTree->RootNdoe);
    return (rootNode);
}

BinTreeNode	*getRightChildNodeBT(BinTreeNode* pNode)
{
    BinTreeNode *RightChildNode;
    
    if (pNode == NULL || pNode->pRightChild == NULL)
        return (NULL);
    RightChildNode = malloc(sizeof(BinTreeNode));
    if (RightChildNode == NULL)
        return (NULL);
	*RightChildNode = *(pNode->pRightChild);
    return (RightChildNode);
}

BinTreeNode	*peekLeftChildNodeBT(BinTreeNode* pNode) // 포인터로 바꾸기
{
    BinTreeNode *LeftChildNode;

    if (pNode == NULL || pNode->pLeftChild == NULL)
        return (LeftChildNode);
	*(LeftChildNode) = *(pNode->pLeftChild);
    return (LeftChildNode);
}

BinTreeNode	*peekRightChildNodeBT(BinTreeNode* pNode)
{
    BinTreeNode *RightChildNode;

    if (pNode == NULL || pNode->pRightChild == NULL)
        return (RightChildNode);
	*(RightChildNode) = *(pNode->pRightChild);
    return (RightChildNode);
}

void deleteBinTreeNode(BinTreeNode* pNode)
{
    if (pNode == NULL)
        return ;
    deleteBinTreeNode(pNode->pLeftChild);
    deleteBinTreeNode(pNode->pRightChild);
    free(pNode);
}

// BinTree* pBinTree;
// deleteBinTree(&pBinTree)
void    deleteBinTree(BinTree** pBinTree)
{
    if (pBinTree == NULL || *pBinTree == NULL)
        return ;
    deleteBinTreeNode((*pBinTree)->pRootNode);
    free(*pBinTree);
	*pBinTree = NULL;
}

void deleteBinTree(BinTree* pBinTree)
{
    if (pBinTree == NULL)
        return ;
    if (pBinTree->pRootNode != NULL)
        deleteBinTreeNode(pBinTree->pRootNode);
    free(pBinTree);
}

int main()
{
    BinTree *bintree;
    BinTreeNode rootnode;
    BinTreeNode *temp;
    BinTreeNode element;

    rootnode.data = 'a';
    rootnode.pLeftChild = NULL;
    rootnode.pRightChild = NULL;
    rootnode.visited = 0;
    element.data = 'b';
    element.pLeftChild = NULL;
    element.pRightChild = NULL;
    element.visited = 0;
    bintree = makeBinTree(rootnode);
    temp = getRootNodeBT(bintree);
    printf("root data : %c\n", temp->data);

    insertLeftChildNodeBT(bintree->pRootNode, element);
    element.data = 'c';
    insertRightChildNodeBT(bintree->pRootNode, element);

    temp = getLeftChildNodeBT(bintree->pRootNode);
    printf("Left BT data : %c\n", temp->data);
    free(temp);

    temp = getRightChildNodeBT(bintree->pRootNode);
    printf("Right BT data : %c\n", temp->data);
    free(temp);
}