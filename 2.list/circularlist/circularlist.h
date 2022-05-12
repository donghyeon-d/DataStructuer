#ifndef _CIRCULARLIST_
#define _CIRCULARLIST_



typedef struct CircularListNodeType
{
	int data;
	struct CircularListNodeType* pLink;
} CircularNode;

typedef struct CircularLinkedListType
{
	int currentElementCount;	// 현재 노드 개수
	CircularNode headerNode;		// 해더 노드(Header Node)
} CircularList;

CircularList* createCircularList();
CircularNode createCircularNode(int data);
CircularNode* getCLElement(CircularList* pList, int position);
int addCLElement(CircularList* pList, int position, CircularNode element);
int removeCLElement(CircularList* pList, int position);

void clearCircularList(CircularList* pList);
int getCircularListLength(CircularList* pList);
void deleteCircularList(CircularList* pList);
#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif