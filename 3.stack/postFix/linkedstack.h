#ifndef _LINKED_STACK_
#define _LINKED_STACK_

typedef struct StackNodeType
{
	char data;
	struct StackNodeType* pLink;
} StackNode;

typedef struct LinkedStackType
{
	int currentElementCount;
	StackNode* pTopElement;
} LinkedStack;

LinkedStack* createLinkedStack();
int pushLS(LinkedStack* pStack, StackNode element);
StackNode* popLS(LinkedStack* pStack);
StackNode* peekLS(LinkedStack* pStack);
void deleteLinkedStack(LinkedStack* pStack);
int isLinkedStackEmpty(LinkedStack* pStack);
void displayLinkedStack(LinkedStack* pList);
int	checkBracketMatching(char *str);
void print_line(char *str);


// int isLinkedStackFull(LinkedStack* pStack); ????

int		ft_isoperator(char c);
void	ft_add_operator(LinkedStack *stack, char *result, int *r_idx);
void	ft_add_operand(char *result, char *str, int *r_idx, int *s_idx);
int		ft_operator_priority(char c);

#endif

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE		1
#define FALSE		0
#define ERROR		-1

#endif