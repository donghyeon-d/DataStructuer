#include "arraystack.h"
#include <stdlib.h>
#include <stdio.h>

ArrayStack* createArrayStack(int maxElementCount)
{
    ArrayStack *newStack;

    if (maxElementCount <= 0)
        return (NULL);
    newStack = (ArrayStack *)malloc(sizeof(ArrayStack));
    if (!newStack)
        return (NULL);
    newStack->pElement = malloc(sizeof(StackNode) * maxElementCount);
    if (!newStack->pElement)
	{
		free(newStack);
		return (NULL);
	}
    newStack->maxElementCount = maxElementCount;
    newStack->currentElementCount = 0;
	return (newStack);
}

int isArrayStackFull(ArrayStack* pStack)
{
    if (!pStack)
        return (ERROR);
    if (pStack->maxElementCount == pStack->currentElementCount)
        return (TRUE);
    return (FALSE);
}

int isArrayStackEmpty(ArrayStack* pStack)
{
    if (!pStack)
        return (ERROR);
    if (pStack->currentElementCount == 0)
        return (TRUE);
    return (FALSE);
}

int pushAS(ArrayStack* pStack, StackNode element)
{
    if (!pStack || isArrayStackFull(pStack))
        return (ERROR);
    (pStack->pElement)[pStack->currentElementCount] = element;
    pStack->currentElementCount++;
    return (TRUE);
}

StackNode *popAS(ArrayStack* pStack)
{
    StackNode *temp;

    if (!pStack || isArrayStackEmpty(pStack))
        return (NULL);
    temp = &((pStack->pElement)[pStack->currentElementCount - 1]);
    pStack->currentElementCount--;
    return (temp);
}

StackNode* peekAS(ArrayStack* pStack)
{
    StackNode *temp;

    if (!pStack || isArrayStackEmpty(pStack))
        return (NULL);
    temp = &((pStack->pElement)[pStack->currentElementCount - 1]);
    return (temp);
}

void deleteArrayStack(ArrayStack* pStack)
{
    if (!pStack)
        return ;
	if (pStack->pElement)
    	free(pStack->pElement);
    free(pStack);
}

void displayArrayStack(ArrayStack* pStack)
{
	int	position;

	if (pStack == NULL)
	{
		printf("ArrayStack is NULL\n");
		return ;
	}
	else if (pStack->currentElementCount == 0)
	{
		printf("ArrayStack is empty\n");
		return ;
	}
	position = 0;
	while (position < pStack->currentElementCount)
	{
		printf("ArrayStack[%d] : %c\n", position, pStack->pElement[position].data);
		position++;
	}
}

void	print_line(char *str)
{
	char *line = "----------";
	printf("%s%s%s\n", line, str, line);
}

// int main()
// {
//     ArrayStack *newStack;

//     newStack = createArrayStack(5);
//     print_line("empty test");
//     printf("empty result : %d", isArrayStackEmpty(newStack));
//     printf("\n\n");
    
//     print_line("pushTest");
//     printf("push result : %d\n", pushAS(newStack, (StackNode){'a'}));
//     printf("push result : %d\n", pushAS(newStack, (StackNode){'b'}));
//     printf("push result : %d\n", pushAS(newStack, (StackNode){'c'}));
//     printf("push result : %d\n", pushAS(newStack, (StackNode){'d'}));
//     printf("push result : %d\n", pushAS(newStack, (StackNode){'e'}));
//     displayArrayStack(newStack);
//     printf("\n\n");

//     print_line("Full test");
//     printf("full result : %d", isArrayStackFull(newStack));
//     printf("\n\n");

//     print_line("peekTest");
// 	printf("peekNode data : %c\n", peekAS(newStack)->data);
// 	displayArrayStack(newStack);
// 	printf("\n\n");

//     print_line("popTest");
// 	printf("popNode data : %c\n", popAS(newStack)->data);
// 	displayArrayStack(newStack);
// 	printf("\n\n");

//     deleteArrayStack(newStack);
// 	return (0);
// }
