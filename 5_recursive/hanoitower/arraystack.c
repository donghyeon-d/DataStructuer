#include "hanoitower.h"

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
//새로 푸쉬되면 값이 바뀌니까, 주소가 아니라 값을 받아서 리턴해주거나 복사해서 리턴해줘야할듯

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
    printf("top |");
	while (position < pStack->currentElementCount)
	{
		printf(" %d |", pStack->pElement[position].data);
		position++;
	}
    printf(" bottom\n");
}

void	print_line(char *str)
{
	char *line = "----------";
	printf("%s%s%s\n", line, str, line);
}
