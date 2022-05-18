#ifndef _ARRAY_BIN_TREE_
#define _ARRAY_BIN_TREE_

typedef struct ArrayBinTreeNodeType
{
	int data;
} ArrayBinTreeNode;

typedef struct ArrayBinTreeType
{
	int maxElementCount;		// 최대 원소 개수
	int currentElementCount;	// 현재 원소의 개수
	ArrayBinTreeNode *pElement;	// 원소 저장을 위한 1차원 배열
} ArrayBinTree;

ArrayBinTree		*makeArrayBinTree(int maxElementCount);
int					isArrayBinTreeFull(ArrayBinTree *pbintree);
int					isArrayBinTreeEmpty(ArrayBinTree *pbintree);
int					insertLeftChildNodeABT(ArrayBinTree	*bintree, int rootIndex, int data);//index return
int					insertRightChildNodeABT(ArrayBinTree	*bintree, int rootIndex, int data);//index return
int					insertInorder(ArrayBinTree	*bintree, int data);
int					searchDataIndex(ArrayBinTree	*bintree, int data);
ArrayBinTreeNode	*deleteArrayBinTree(ArrayBinTree *pbintree);
void				displayArrayBinTree(ArrayBinTree	*arraybintree);

#endif