#include "linkedstack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char	*postFix(char *str)
{
	LinkedStack	*stack;
	StackNode	*temp;
    char        *result;
	int			r_idx;
	int			s_idx;

	if (!str)
		return (NULL);
    if (!checkBracketMatching(str))
        return (NULL);
	stack = createLinkedStack();
	if (!stack)
		return (NULL);
    result = malloc(sizeof(char) * (strlen(str) + 1));
    if (!result)
	{
		deleteLinkedStack(stack);
		return (NULL);
	}
	s_idx = 0;
	r_idx = 0;
	while (str[s_idx])
    {
		if (str[s_idx] == ' ')
			s_idx++;
		// 연산자
		else if (ft_isoperator(str[s_idx]))
		{
			// 음수일 경우
			if (str[s_idx] == '-' && str[s_idx + 1] != ' ')
				ft_add_operand(result, str, &r_idx, &s_idx);
			else
			{
				// stack의 topData(연산자)가 현재 연산자 보다 우선이라면 result에 추가
	        	while (!isLinkedStackEmpty(stack) && ft_operator_priority(peekLS(stack)->data)\
				 > ft_operator_priority(str[s_idx]))
					ft_add_operator(stack, result, &r_idx);
				pushLS(stack, (StackNode){str[s_idx++], NULL});
			}
		}
		// 닫는 괄호
		else if (ft_operator_priority(str[s_idx]) == 3)
        {
			// 여는 괄호를 만날 때 까지
            while (ft_operator_priority(peekLS(stack)->data) != 0)
				ft_add_operator(stack, result, &r_idx);
			temp = popLS(stack);
			free(temp);
			s_idx++;
        }
		// 여는 괄호 '('
		else if (ft_operator_priority(str[s_idx]) == 0)
			pushLS(stack, (StackNode){str[s_idx++], NULL});
		// 피연산자
		else
			ft_add_operand(result, str, &r_idx, &s_idx);
    }
	// 스택에 남은 데이터 pop
    while (!isLinkedStackEmpty(stack))
		ft_add_operator(stack, result, &r_idx);
    deleteLinkedStack(stack);
	result[r_idx] = '\0';
    return (result);
}

int main()
{
    char	*ret;

	print_line("TEST 1");
	printf("%s\n", "A * ( B + C )");
    ret = postFix("A * ( B + C )");
    printf("%s\n", ret);
	free(ret);
	printf("\n\n");

	print_line("TEST 2");
	printf("%s\n", "2 - (3 + 4) * 5");
    ret = postFix("2 - (3 + 4) * 5");
    printf("%s\n", ret);
	free(ret);
	printf("\n\n");

	print_line("TEST 3");
	printf("%s\n", "6 / [{2 + 2 + (8 + -10)} * 1] + 12");
    ret = postFix("6 / [{2 + 2 + (8 + -10)} * 1] + 12");
    printf("%s\n", ret);
	free(ret);
	printf("\n\n");
    return (0);
}