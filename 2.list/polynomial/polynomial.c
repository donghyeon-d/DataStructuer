#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

PolyList* createPolyList()
{
    PolyList *newPolyList;

    newPolyList = (PolyList *)malloc(sizeof(PolyList));
    if (newPolyList == NULL)
        return (NULL);
    newPolyList->currentElementCount = 0;
    newPolyList->headnode.pLink = NULL;
    return (newPolyList);
}

PolyNode *createPolyNode(float coef, int degree)
{
    PolyNode *new;

    new = (PolyNode *)malloc(sizeof(PolyNode));
    if (new == NULL)
        return (NULL);
    new->coef = coef;
    new->degree = degree;
    new->pLink = NULL;
    return (new);
}

PolyNode *getPolyDegreeNode(PolyList *pList, int degree)
{
    int i;
    PolyNode *ret;

    if (pList == NULL)
        return (FALSE);
    ret = &(pList->headnode);
    i = 0;
    while (i < pList->currentElementCount)
    {
        ret = ret->pLink;
        if (ret->degree == degree)
            return (ret);
        i++;
    }
    return (NULL);
}

int addPolyNodeLast(PolyList *pList, float coef, int degree)
{
    int i;
    PolyNode *temp;
    PolyNode *add;

    add = createPolyNode(coef, degree);
    if (pList == NULL || add == NULL)
        return (FALSE);
    i = 0;
    temp = &(pList->headnode);
    while (temp->pLink != NULL)
        temp = temp->pLink;
    temp->pLink = add;
    pList->currentElementCount++;
    return (TRUE);
}

void PolyListDel(PolyList *pList)
{
    PolyNode *temp;
    PolyNode *del;
    int i;

    i = 0;
    temp = pList->headnode.pLink;
    while (temp != NULL)
    {
        del = temp;
        temp = temp->pLink;
        free(del);
    }
    free(pList);
}

PolyList *addPoly(PolyList *pList_A, PolyList *pList_B)
{
    PolyList *ret;
    PolyNode *tempA;
    PolyNode *tempB;
    int i;

    ret = createPolyList();
    tempA = pList_A->headnode.pLink;
    tempB = pList_B->headnode.pLink;
    if (pList_A->currentElementCount > pList_B->currentElementCount)
        i = pList_A->currentElementCount;
    else
        i = pList_B->currentElementCount;
    if ((tempA == NULL && tempB == NULL) || ret == NULL)
        return (NULL);
    while (tempA != NULL && tempB != NULL)
    {
        if (tempA->degree == tempB->degree)
        {
            addPolyNodeLast (ret, tempA->coef + tempB->coef, tempA->degree);
            tempA = tempA->pLink;
            tempB = tempB->pLink;
        }
        else if (tempA->degree > tempB->degree)
        {
            addPolyNodeLast (ret, tempA->coef, tempA->degree);
            tempA = tempA->pLink;
        }
        else if (tempA->degree < tempB->degree)
        {
            addPolyNodeLast (ret, tempB->coef, tempB->degree);
            tempB = tempB->pLink;
        }
    }
    if (tempA == NULL)
    {
        while (tempB != NULL)
        {
            addPolyNodeLast (ret, tempB->coef, tempB->degree);
            tempB = tempB->pLink;
        }
    }
    else if (tempB == NULL)
    {
        while (tempA != NULL)
        {
            addPolyNodeLast (ret, tempA->coef, tempA->degree);
            tempA = tempA->pLink;
        }
    }
    return (ret);
}

void PolyDisplay(PolyList *pList)
{
    PolyNode *node;
    int i;

    if (pList == NULL)
        printf("List is NULL");
    i = 0;
    node = pList->headnode.pLink;
    if (node == NULL)
        printf("Poly is empty");
    while (node != NULL)
    {
        printf("coef : %f | degree : %d\n", node->coef, node->degree);
        node = node->pLink;
    }
}

int main()
{
    PolyList *pListA;
    PolyList *pListB;
    PolyList *result;
    PolyNode *nodeA;
    PolyNode *nodeB;

    pListA = createPolyList();
    pListB = createPolyList();
    addPolyNodeLast(pListA, 6, 6);
    addPolyNodeLast(pListA, 4, 5);
    addPolyNodeLast(pListA, 2, 2);

    addPolyNodeLast(pListB, 1, 5);
    addPolyNodeLast(pListB, 2, 4);
    addPolyNodeLast(pListB, 3, 2);
    addPolyNodeLast(pListB, 4, 0);
    // PolyDisplay(pListA);
    // PolyDisplay(pListB);
    result = addPoly(pListA, pListB);
    PolyDisplay(result);
}