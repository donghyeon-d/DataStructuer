#ifndef _POLUNOMIAL_
#define _POLUNOMIAL_

typedef struct PolynomialNode
{
    float coef;
    int degree;
    struct PolynomialNode *pLink;
} PolyNode;

typedef struct PolynomialList
{
    int currentElementCount;
    PolyNode headnode;
} PolyList;

PolyList *createPolyList();
PolyNode *createPolyNode(float coef, int degree);
PolyNode *getPolyDegreeNode(PolyList *pList, int degree); // degree에 해당하는 노드 찾기. 없으면 NULL
int addPolyNodeLast(PolyList *pList, float coef, int degree);
void PolyListDel(PolyList *pList);
PolyList *addPoly(PolyList *pList_A, PolyList *pList_B);


#endif


#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif