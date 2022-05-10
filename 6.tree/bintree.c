#include <stdlib.h>
#include <stdio.h>
#include "bintree.h"

BinTree *makeBinTree(BinTreeNode rootNode)
{
    BinTree *bintree;

    bintree = malloc(sizeof(BinTree));
    if (bintree == NULL)
        return (NULL);
    bintree->pRootNode = &rootNode;
    return (bintree);
}

BinTreeNode *getRootNodeBT(BinTree* pBinTree)
{
    BinTreeNode *rootNode;

    if (pBinTree == NULL)
        return (NULL);
    rootNode = malloc(sizeof(BinTreeNode));
    if (rootNode == NULL)
        return (NULL);
    
    rootNode->data = pBinTree->pRootNode->data;
    rootNode->visited = pBinTree->pRootNode->visited;
    rootNode->pLeftChild = pBinTree->pRootNode->pLeftChild;
    rootNode->pRightChild = pBinTree->pRootNode->pRightChild;
    return (rootNode);
}

BinTreeNode *insertLeftChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    BinTreeNode *LeftChildNode;
    
    if (pParentNode == NULL)
        return (NULL);
    LeftChildNode = malloc(sizeof(BinTreeNode));
    if (LeftChildNode == NULL)
        return (NULL);
    LeftChildNode->data = element.data;
    LeftChildNode->pLeftChild = NULL;
    LeftChildNode->pRightChild = NULL;
    LeftChildNode->visited = 0;
    pParentNode->pLeftChild = LeftChildNode;
    return (LeftChildNode);
}

BinTreeNode* insertRightChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    BinTreeNode *rightChildNode;
    
    if (pParentNode == NULL)
        return (NULL);
    rightChildNode = malloc(sizeof(BinTreeNode));
    if (rightChildNode == NULL)
        return (NULL);
    rightChildNode->data = element.data;
    rightChildNode->pLeftChild = NULL;
    rightChildNode->pRightChild = NULL;
    rightChildNode->visited = 0;
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
    LeftChildNode->data = pNode->pLeftChild->data;
    LeftChildNode->pLeftChild = pNode->pLeftChild->pLeftChild;
    LeftChildNode->pRightChild = pNode->pLeftChild->pRightChild;
    LeftChildNode->visited = pNode->pLeftChild->visited;
    return (LeftChildNode);
}

BinTreeNode* getRightChildNodeBT(BinTreeNode* pNode)
{
    BinTreeNode *RightChildNode;
    
    if (pNode == NULL || pNode->pRightChild == NULL)
        return (NULL);
    RightChildNode = malloc(sizeof(BinTreeNode));
    if (RightChildNode == NULL)
        return (NULL);
    RightChildNode->data = pNode->pRightChild->data;
    RightChildNode->pLeftChild = pNode->pRightChild->pLeftChild;
    RightChildNode->pRightChild = pNode->pRightChild->pRightChild;
    RightChildNode->visited = pNode->pRightChild->visited;
    return (RightChildNode);
}

BinTreeNode peekLeftChildNodeBT(BinTreeNode* pNode)
{
    BinTreeNode LeftChildNode;

    LeftChildNode.data = 0;
    LeftChildNode.pLeftChild = NULL;
    LeftChildNode.pRightChild = NULL;
    LeftChildNode.visited = 0;
    if (pNode == NULL || pNode->pLeftChild == NULL)
        return (LeftChildNode);
    LeftChildNode.data = pNode->data;
    LeftChildNode.pLeftChild = pNode->pLeftChild;
    LeftChildNode.pRightChild = pNode->pRightChild;
    LeftChildNode.visited = pNode->visited;
    return (LeftChildNode);
}

BinTreeNode peekRightChildNodeBT(BinTreeNode* pNode)
{
    BinTreeNode RightChildNode;

    RightChildNode.data = 0;
    RightChildNode.pLeftChild = NULL;
    RightChildNode.pRightChild = NULL;
    RightChildNode.visited = 0;
    if (pNode == NULL || pNode->pLeftChild == NULL)
        return (RightChildNode);
    RightChildNode.data = pNode->data;
    RightChildNode.pLeftChild = pNode->pLeftChild;
    RightChildNode.pRightChild = pNode->pRightChild;
    RightChildNode.visited = pNode->visited;
    return (RightChildNode);
}

void deleteBinTreeNode(BinTreeNode* pNode)
{
    if (pNode == NULL)
        return ;
    if (pNode->pLeftChild != NULL)
        free(pNode->pLeftChild);
    if (pNode->pRightChild != NULL)
        free(pNode->pRightChild);
    free(pNode);
    return ;
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