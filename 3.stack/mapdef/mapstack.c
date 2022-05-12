#include "mapdef.h"
#include <stdlib.h>
#include <stdio.h>

MapStack* createMapStack()
{
	MapStack *newStack;

	newStack = (MapStack *)malloc(sizeof(MapStack));
	if (newStack == NULL)
		return (NULL);
	newStack->currentElementCount = 0;
	newStack->pTopElement = NULL;
	return (newStack);
}

int pushLS(MapStack* pStack, MapPosition element)
{
	MapPosition	*newNode;

	if (!pStack)
		return (ERROR);
	newNode = malloc(sizeof(MapPosition));
	if (!newNode)
		return (FALSE);
	newNode->x = element.x;
	newNode->y = element.y;
	newNode->direction = element.direction;
	newNode->cnt = element.cnt;
	newNode->pLink = pStack->pTopElement;
	pStack->pTopElement = newNode;
	pStack->currentElementCount++;
	return (TRUE);
}

MapPosition* popLS(MapStack* pStack)
{
	MapPosition	*popNode;

	if (!pStack || !pStack->pTopElement)
		return (NULL);
	popNode = pStack->pTopElement;
	pStack->pTopElement = pStack->pTopElement->pLink;
	popNode->pLink = NULL;
	pStack->currentElementCount--;
	return (popNode);
}

MapPosition* peekLS(MapStack* pStack)
{
	if (!pStack)
		return (FALSE);
	return (pStack->pTopElement);
}

int isMapStackEmpty(MapStack* pStack)
{
	if (!pStack)
		return (ERROR);
	if (!pStack->currentElementCount)
		return (TRUE);
	return (FALSE);
}

void deleteMapStack(MapStack* pStack)
{
	MapPosition	*delStack;
    
	if (!pStack)
		return ;
	while (pStack->pTopElement)
	{
		delStack = popLS(pStack);
		free(delStack);
	}
	free(pStack);
}

// MapPosition	copyPosition(MapPosition *curPos)
// {
// 	MapPosition	copy;

// 	copy.x = curPos->x;
// 	copy.y = curPos->y;
// 	copy.direction = curPos->direction;
// 	return (copy);
// }

void	print_line(char *str)
{
	char *line = "----------";
	printf("%s%s%s\n", line, str, line);
}
