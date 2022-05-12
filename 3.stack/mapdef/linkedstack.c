#include "linkedstack.h"
#include <stdlib.h>
#include <stdio.h>
//12페이지

LinkedStack* createLinkedStack()
{
	LinkedStack *newStack;

	newStack = (LinkedStack *)malloc(sizeof(LinkedStack));
	if (newStack == NULL)
		return (NULL);
	newStack->currentElementCount = 0;
	newStack->pTopElement = NULL;
	return (newStack);
}

int pushLS(LinkedStack* pStack, StackNode element)
{
	StackNode	*newNode;

	if (!pStack)
		return (ERROR);
	newNode = malloc(sizeof(StackNode));
	if (!newNode)
		return (FALSE);
	newNode->data = element.data;
	newNode->pLink = pStack->pTopElement;
	pStack->pTopElement = newNode;
	pStack->currentElementCount++;
	return (TRUE);
}

StackNode* popLS(LinkedStack* pStack)
{
	StackNode	*popNode;

	if (!pStack || !pStack->pTopElement)
		return (NULL);
	popNode = pStack->pTopElement;
	pStack->pTopElement = pStack->pTopElement->pLink;
	popNode->pLink = NULL;
	pStack->currentElementCount--;
	return (popNode);
}//함수 밖에서 free 해줘야 함

StackNode* peekLS(LinkedStack* pStack)
{
	if (!pStack)
		return (FALSE);
	return (pStack->pTopElement);
}

int isLinkedStackEmpty(LinkedStack* pStack)
{
	if (!pStack)
		return (ERROR);
	if (!pStack->currentElementCount)
		return (TRUE);
	return (FALSE);
}

void deleteLinkedStack(LinkedStack* pStack)
{
	StackNode	*delStack;
    
	if (!pStack)
		return ;
	while (pStack->pTopElement)
	{
		delStack = popLS(pStack);
		free(delStack);
	}
	free(pStack);
}

void displayLinkedStack(LinkedStack* pList)
{
	StackNode	*temp;
	int			position;

	if (pList == NULL)
	{
		printf("LinkedStack is NULL\n");
		return ;
	}
	else if (pList->currentElementCount == 0)
	{
		printf("LinkedStack is empty\n");
		return ;
	}
	temp = pList->pTopElement;
	position = 0;
	while (temp)
	{
		printf("LinkedStack[%d] : %c\n", position, temp->data);
		temp = temp->pLink;
        position++;
	}
}

void	print_line(char *str)
{
	char *line = "----------";
	printf("%s%s%s\n", line, str, line);
}

int	main()
{
	LinkedStack	*stack;
	StackNode	*temp;

	stack = createLinkedStack();
	print_line("emptyTest");
	printf("empty result : %d", isLinkedStackEmpty(stack));
	printf("\n\n");

	print_line("pushTest");
	printf("push result : %d\n", pushLS(stack, (StackNode){'a', NULL}));
	printf("push result : %d\n", pushLS(stack, (StackNode){'b', NULL}));
	printf("push result : %d\n", pushLS(stack, (StackNode){'c', NULL}));
	printf("push result : %d\n", pushLS(stack, (StackNode){'d', NULL}));
	printf("push result : %d\n", pushLS(stack, (StackNode){'e', NULL}));
	displayLinkedStack(stack);
	printf("\n\n");
	
	print_line("peekTest");
	printf("peekNode data : %c\n", peekLS(stack)->data);
	displayLinkedStack(stack);
	printf("\n\n");

	print_line("popTest");
	temp = popLS(stack);
	printf("popNode data : %c\n", temp->data);
	displayLinkedStack(stack);
	free(temp);
	printf("\n\n");

	deleteLinkedStack(stack);
	displayLinkedStack(stack);
	return 0;
}
