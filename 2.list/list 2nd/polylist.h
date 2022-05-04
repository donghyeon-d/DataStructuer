#ifndef _POLYLIST_
#define _POLYLIST_

typedef struct PolyListNodeType
{
	int coef;
    int degree;
	struct PolyListNodeType* pLink;
} PolyListNode;

int addPolyNodeLast(LinkedList* pList, int coef, int degree);
LinkedList* polyAdd(LinkedList* pListA, LinkedList* pListB);
void displayPolyList(LinkedList* pList);

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif