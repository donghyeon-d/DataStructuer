#include <stdlib.h>
#include "bintree.h"

BinTree*    makeBinTree(BinTreeNode rootNode)
{
    BinTree*    newTree;

    newTree = malloc(sizeof(BinTree));
    if (newTree == NULL)
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

BinTreeNode*    getRootNodeBT(BinTree* pBinTree)
{
    if (pBinTree == NULL)
        return (NULL);
    return (pBinTree->pRootNode);
}

BinTreeNode*    insertLeftChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    BinTreeNode*    newNode;

    if (pParentNode == NULL || pParentNode->pLeftChild != NULL)
        return (NULL);
    newNode = malloc(sizeof(BinTreeNode));
    if (newNode == NULL)
        return (NULL);
    *newNode = element;
    pParentNode->pLeftChild = newNode;
    return (newNode);
}

BinTreeNode*    insertRightChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    BinTreeNode*    newNode;

    if (pParentNode == NULL || pParentNode->pRightChild != NULL)
        return (NULL);
    newNode = malloc(sizeof(BinTreeNode));
    if (newNode == NULL)
        return (NULL);
    *newNode = element;
    pParentNode->pRightChild = newNode;
    return (newNode);
}

BinTreeNode*    getLeftChildNodeBT(BinTreeNode* pNode)
{
    if (pNode == NULL)
        return (NULL);
    return (pNode->pLeftChild);
}

BinTreeNode*    getRightChildNodeBT(BinTreeNode* pNode)
{
    if (pNode == NULL)
        return (NULL);
    return (pNode->pRightChild);
}

void    deleteBinTree(BinTree* pBinTree)
{
    if (pBinTree == NULL)
        return ;
    deleteBinTreeNode(pBinTree->pRootNode);
    free(pBinTree);
}

 // pNode가 NULL로 초기화가 안되기 때문에, pNode의 부모노드는 여전히 자식을 갖고있는거로 됨. 널 초기화 필요(함수 안이든 밖이든)
 // 함수 밖에서  pNode의 부모->pNode = NULL; 해줘야함
void    deleteBinTreeNode(BinTreeNode* pNode)
{
    if (pNode == NULL)
        return ;
    deleteBinTreeNode(pNode->pLeftChild);
    deleteBinTreeNode(pNode->pRightChild);
    free(pNode);
}
