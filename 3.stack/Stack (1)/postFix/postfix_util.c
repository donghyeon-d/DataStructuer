#include "linkedstack.h"
#include <stdlib.h>

int	ft_isoperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return (TRUE);
	return (FALSE);
}

int ft_operator_priority(char c)
{
    if (c == '(' || c == '{' || c == '[')
        return (0);
    else if (c == '+' || c == '-')
        return (1);
    else if (c == '*' || c == '/')
        return (2);
    else if (c == ')' || c == '}' || c == ']')
        return (3);
	return (-1);
}

void	ft_add_operator(LinkedStack *stack, char *result, int *r_idx)
{
	StackNode	*temp;
	int			idx;

	idx = *r_idx;
	result[idx++] = ' ';
	temp = popLS(stack);
	result[idx++] = temp->data;
	free(temp);
	*r_idx = idx;
}

void	ft_add_operand(char *result, char *str, int *r_idx, int *s_idx)
{
	int	r;
	int	s;

	r = *r_idx;
	s = *s_idx;
	if (s)
		result[r++] = ' ';
	if (str[s] == '-')
		result[r++] = str[s++];
	while (str[s] && ft_operator_priority(str[s]) < 0)
	{
		if (str[s] == ' ')
			break ;
		result[r++] = str[s++];
	}
	*r_idx = r;
	*s_idx = s;
}
