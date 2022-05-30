#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"
#include "bintraversal.h"

BinTreeNode*    insertNodeBST(BinTree* pBinTree, BinTreeNode element)
{
    BinTreeNode*    newNode;
    BinTreeNode*    parent;
    BinTreeNode*    child;

    if (pBinTree == NULL)
        return (NULL);
    newNode = malloc(sizeof(BinTreeNode));
    if (newNode == NULL)
        return (NULL);
    *newNode = element;
    child = pBinTree->pRootNode;
    if (child == NULL)
        child = newNode;
    while (child != NULL)
    {
        if (element.data == child->data)
        {
            free(newNode);
            return (NULL);
        }
        parent = child;
        if (element.data < child->data)
            child = child->pLeftChild;
        else
            child = child->pRightChild;
    }
    if (element.data < parent->data)
        parent->pLeftChild = newNode;
    else
        parent->pRightChild = newNode;
    return (newNode);
}

void    deleteBSTNode(BinTree* pBinTree, BinTreeNode element)
{
    BinTreeNode*    prev;
    BinTreeNode*    curr;
    BinTreeNode*    delNode;

    if (pBinTree == NULL || pBinTree->pRootNode == NULL)
        return ;
    prev = NULL;
    delNode = pBinTree->pRootNode;
    while (delNode != NULL)
    {
        if (element.data == delNode->data)
            break ;
        prev = delNode;
        if (element.data < delNode->data)
            delNode = delNode->pLeftChild;
        else
            delNode = delNode->pRightChild;
    }
    if (delNode == NULL)    // Node not found
        return ;
    curr = delNode;
    if (curr->pLeftChild == NULL && curr->pRightChild == NULL)
    {
        if (prev == NULL)
            pBinTree->pRootNode = NULL;
        else if (element.data < prev->data)
            prev->pLeftChild = NULL;
        else
            prev->pRightChild = NULL;
    }
    else if (curr->pLeftChild == NULL)
    {
        prev = curr;
        delNode = curr->pRightChild;
        while (delNode->pLeftChild != NULL)
        {
            prev = delNode;
            delNode = delNode->pLeftChild;
        }
        curr->data = delNode->data;
        prev->pLeftChild = delNode->pRightChild;
    }
    else
    {
        prev = curr;
        delNode = curr->pLeftChild;
        while (delNode->pRightChild != NULL)
        {
            prev = delNode;
            delNode = delNode->pRightChild;
        }
        curr->data = delNode->data;
        prev->pRightChild = delNode->pLeftChild;
    }
    free(delNode);
}

BinTreeNode*    searchBSTNode(BinTree* pBinTree, BinTreeNode element)
{
    BinTreeNode*    curr;

    if (pBinTree == NULL)
        return (NULL);
    curr = pBinTree->pRootNode;
    while (curr != NULL)
    {
        if (element.data == curr->data)
            break ;
        else if (element.data < curr->data)
            curr = curr->pLeftChild;
        else
            curr = curr->pRightChild;
    }
    return (curr);
}

int main(void)
{
    BinTree*    BST;
    BinTreeNode dummy = {.pLeftChild = NULL, .pRightChild = NULL};

    dummy.data = 30;
    BST = makeBinTree(dummy);
    dummy.data = 20;
    insertNodeBST(BST, dummy);
    dummy.data = 40;
    insertNodeBST(BST, dummy);
    dummy.data = 10;
    insertNodeBST(BST, dummy);
    dummy.data = 24;
    insertNodeBST(BST, dummy);
    dummy.data = 34;
    insertNodeBST(BST, dummy);
    dummy.data = 46;
    insertNodeBST(BST, dummy);
    dummy.data = 6;
    insertNodeBST(BST, dummy);
    dummy.data = 14;
    insertNodeBST(BST, dummy);
    dummy.data = 22;
    insertNodeBST(BST, dummy);

    inorderTraversalBinTree(BST);
    printf("\n");

    dummy.data = 25;
    printf("search: %p\n", searchBSTNode(BST, dummy));

    dummy.data = 30;
    deleteBSTNode(BST, dummy);
    inorderTraversalBinTree(BST);
    return (0);
}
