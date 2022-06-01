#ifndef _LINKED_STACK_
#define _LINKED_STACK_

typedef struct StackNodeType
{
	int 	vertexID;
	struct	StackNodeType* pLink;
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

// int isLinkedStackFull(LinkedStack* pStack); ????
#endif

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE		1
#define FALSE		0
#define ERROR		-1

#endif