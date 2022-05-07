#ifndef _HANOITOWER_
#define _HANOITOWER_

#include <stdlib.h>
#include <stdio.h>

typedef struct StackNodeType
{
	char data;
} StackNode;

typedef struct ArrayStackType
{
	int maxElementCount;		// 최대 원소 개수
	int currentElementCount;	// 현재 원소의 개수
	StackNode* pElement;
} ArrayStack;

ArrayStack *createArrayStack(int maxElementCount);
int pushAS(ArrayStack* pStack, StackNode element);
StackNode *popAS(ArrayStack* pStack);
StackNode *peekAS(ArrayStack* pStack);
void deleteArrayStack(ArrayStack* pStack);
int isArrayStackFull(ArrayStack* pStack);
int isArrayStackEmpty(ArrayStack* pStack);
void displayArrayStack(ArrayStack* pStack);

#endif

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE		1
#define FALSE		0
#define	ERROR		-1

#endif