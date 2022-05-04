#ifndef _POLYLIST_
#define _POLYLIST_

typedef struct PolyListNodeType
{
	int coef;
    int degree;
	struct PolyListNodeType* pLink;
} PolyListNode;

typedef struct PolyListType
{
	int currentElementCount;	// 현재 저장된 원소의 개수
	PolyListNode headerNode;		// 헤더 노드(Header Node)
} PolyList;

int addPolyNodeLast(PolyList* pList, int coef, int degree);
PolyList* polyAdd(PolyList* pListA, PolyList* pListB);
void displayPolyList(PolyList* pList);

PolyList* createPolyList();
int addPLElement(PolyList* pList, int position, PolyListNode element);
PolyListNode* getPLElement(PolyList* pList, int position);

int removePLElement(PolyList* pList, int position);
void clearPolyList(PolyList* pList);
int getPolyListLength(PolyList* pList);
void deletePolyList(PolyList* pList);

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif