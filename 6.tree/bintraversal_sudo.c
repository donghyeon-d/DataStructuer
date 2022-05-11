#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

void    preorderTraversal(BinTreeNode *rootNode)
{
    if (rootNode == NULL)
        return (NULL);
    if(왼쪽 자식 == 널 && 오른쪽 자식 == 널)
        return (NULL);
    printf(rootNode->data);
    rootNode->visited = 1;
    if (왼쪽 자식 != 널)
        preorderTraversal(왼쪽 자식 노드);
    if (오른쪽 자식 != 널)
        preorderTraversal(오른쪽 자식 노드);
}

void    inorderTraversal(BinTreeNode *rootNode)
{
    if (rootNode == NULL)
        return (NULL);
    if(왼쪽 자식 == 널 && 오른쪽 자식 == 널)
    {
        printf(rootNode->data);
        rootNode->visited = 1;
        return (NULL);
    }
    if (!왼쪽 자식->visited)
        preorderTraversal(왼쪽 자식 노드);
    if (!rootNode->visited)
    {
        printf(rootNode->data);
        rootNode->visited = 1;
    }
    if (!오른쪽 자식->visited)
        preorderTraversal(오른쪽 자식 노드);
}

void    posorderTraversal(BinTreeNode *rootNode)
{
    if (rootNode == NULL)
        return (NULL);
    if(왼쪽 자식 == 널 && 오른쪽 자식 == 널)
    {
        printf(rootNode->data);
        rootNode->visited = 1;
        return (NULL);
    }
    if (!왼쪽 자식->visited)
        preorderTraversal(왼쪽 자식 노드);
    if (!오른쪽 자식->visited)
        preorderTraversal(오른쪽 자식 노드);
    if (!rootNode->visited)
    {
        printf(rootNode->data);
        rootNode->visited = 1;
    }
}