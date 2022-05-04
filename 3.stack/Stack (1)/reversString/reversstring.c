#include "arraystack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char	*reversString(char *str)
{
	ArrayStack	*stack;
	char		*revers;
	int			idx;

    if (!str)
		return (NULL);
	stack = createArrayStack(strlen(str));
	if (!stack)
		return (NULL);
	revers = malloc(sizeof(char) * (strlen(str) + 1));
	if (!revers)
	{
		deleteArrayStack(stack);
		return (NULL);
	}
	idx = 0;
	while (str[idx])
		pushAS(stack, (StackNode){str[idx++]});
	idx = 0;
	while (stack->currentElementCount)
		revers[idx++] = (popAS(stack))->data;
    deleteArrayStack(stack);
	return (revers);
}

int	main()
{
	char	*str = "abcdefg";
	char	*revers = reversString(str);
	printf("%s\n", str);
	printf("%s\n", revers);
	free(revers);
	return (0);
}
