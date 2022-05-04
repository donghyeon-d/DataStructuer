#include "linkedstack.h"
#include <stdlib.h>
#include <stdio.h>

static int ft_isbraket(char c)
{
    if (c == '{' || c == '(' || c == '[')
        return (1);
    else if (c == '}' || c == ')' || c == ']')
		return (2);
    return (FALSE);
}

static int	ft_braketcmp(char c1, char c2)
{
	if (c1 == '{' && c2 == '}')
		return (TRUE);
	else if (c1 == '(' && c2 == ')')
		return (TRUE);
	else if (c1 == '[' && c2 == ']')
		return (TRUE);
	return (FALSE);
}

int	checkBracketMatching(char *str)
{
    LinkedStack *bStack;
	StackNode	*temp;
    int         idx;
	int			braket_bool;

	if (!str)
		return (ERROR);
	bStack = createLinkedStack();
	if (!bStack)
		return (FALSE);
    idx = 0;
    while (str[idx])
    {
		braket_bool = ft_isbraket(str[idx]);
        if (braket_bool == 1)
            pushLS(bStack, (StackNode){str[idx], NULL});
        else if (braket_bool == 2)
		{
			temp = popLS(bStack);
            if (!temp || !ft_braketcmp(temp->data, str[idx]))
			{
				free(temp);
            	deleteLinkedStack(bStack);
            	return (FALSE);
			}
			free(temp);
        }
        idx++;
    }
	if (!isLinkedStackEmpty(bStack))
	{
		deleteLinkedStack(bStack);
		return (FALSE);
	}
    deleteLinkedStack(bStack);
    return (TRUE);
}

int main()
{
	char *str1 = "( ( A * B ) / C ) - { ( D + E ) && ( F - G ) }";
	char *str2 = "( ( A * B ) / C - { ( D + E ) && ( F - G ) ) }";
    char *str3 = "}( ( A * B ) / C - { ( D + E ) && ( F - G ) ) }";
    char *str4 = "( ( A * B ) / C ) - { ( D + E ) && ( F - G ) }(";
    printf("braket check (TRUE) : %d\n\n", checkBracketMatching(str1));
    printf("braket check (FALSE) : %d\n\n", checkBracketMatching(str2));
	printf("braket check (FALSE) : %d\n\n", checkBracketMatching(str3));
	printf("braket check (FALSE) : %d\n", checkBracketMatching(str4));
}