#include "linkedstack.h"
#include <stdlib.h>
#include <stdio.h>

LinkedStack* createLinkedStack()
{
    LinkedStack *tmp;
    
    tmp = (LinkedStack *)malloc(sizeof(LinkedStack));
    if (!tmp)
        return (FALSE);
    tmp->currentElementCount = 0;
    tmp->pTopElement = NULL;
    return (tmp);
}

int pushLS(LinkedStack* pStack, StackNode element)
{
    StackNode *tmp;

    if (!pStack)
        return (FALSE);
    tmp = (StackNode *)malloc(sizeof(StackNode));
    if (!tmp)
        return (FALSE);
    *tmp = element;
    tmp->pLink = pStack->pTopElement;
    pStack->pTopElement = tmp;
    pStack->currentElementCount++;
    return (TRUE);
}

StackNode* popLS(LinkedStack* pStack)
{
    StackNode *ret;

    ret = peekLS(pStack);
    if (ret)
    {
        pStack->pTopElement = pStack->pTopElement->pLink;
        ret->pLink = NULL;
        pStack->currentElementCount--;
    }
    return (ret);
}

StackNode* peekLS(LinkedStack* pStack)
{
    if (!pStack)
        return (NULL);
    if (isLinkedStackEmpty(pStack))
        return (NULL);
    return (pStack->pTopElement);
}

void deleteLinkedStack(LinkedStack* pStack)
{
    StackNode *tmp;

    if (!pStack)
        return ;
    while (!isLinkedStackEmpty(pStack))
    {
        tmp = popLS(pStack);
        if (tmp)
            free(tmp);
    }
    free(pStack);
}

int isLinkedStackEmpty(LinkedStack* pStack)
{
    if (!pStack)
        return (FALSE);
    if (pStack->pTopElement == NULL)
        return (TRUE);
    if (pStack->currentElementCount == 0)
        return (TRUE);
    else
        return (FALSE);
}

void displayLinkedStack(LinkedStack* pStack)
{
    StackNode *tmp;
    int         idx;

    if (!pStack)
    {
        printf("No Stack\n");
        return ;
    }
    else if (isLinkedStackEmpty(pStack))
    {
        printf("Stack is Empty\n");
        return ;
    }
    else
    {
        idx = -1;
        tmp = pStack->pTopElement;
        while (++idx < pStack->currentElementCount - 1)
        {
            printf("%c -> ", tmp->data);
            tmp = tmp->pLink;
        }
        printf("%c\n", tmp->data);
    }
}

/*int main()
{
    LinkedStack *stack;
    StackNode *temp;
    StackNode element;

    stack = createLinkedStack();
    for (int i = 0; i < 10; i++)
    {
        element.data = i + '0';
        element.pLink = NULL;
        pushLS(stack, element);
    }
    displayLinkedStack(stack);
    temp = peekLS(stack);
    printf("peek data : %c\n", temp->data);
    temp = popLS(stack);
    printf("pop data : %c\n", temp->data);
    free(temp);
    displayLinkedStack(stack);
    while (temp = popLS(stack))
        free(temp);
    printf("pop all\n");
    displayLinkedStack(stack);   
    printf("%d\n", isLinkedStackEmpty(stack));
    deleteLinkedStack(stack);
    return (0);
}*/