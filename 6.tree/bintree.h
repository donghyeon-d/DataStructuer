#ifndef _BIN_TREE_
#define _BIN_TREE_

typedef struct BinTreeNodeType
{
	char data;
	int visited;

	struct BinTreeNodeType* pLeftChild;
	struct BinTreeNodeType* pRightChild;
} BinTreeNode;

typedef struct BinTreeType
{
	struct BinTreeNodeType* pRootNode;
} BinTree;

BinTree* makeBinTree(BinTreeNode rootNode);
BinTreeNode* getRootNodeBT(BinTree* pBinTree);
BinTreeNode* insertLeftChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element);//element를 malloc 해서 왼쪽 자식으로 넣어주고, 왼쪽 자식의 주소 리턴
BinTreeNode* insertRightChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element);//element를 malloc 해서 오른쪽 자식으로 넣어주고, 오른쪽 자식의 주소 리턴
BinTreeNode* getLeftChildNodeBT(BinTreeNode* pNode);//왼쪽 자식 노드를 malloc 복사해서 리턴. 복사 안할거면 pNode->pLeftchildeNode로 접근하면 되잖아
BinTreeNode* getRightChildNodeBT(BinTreeNode* pNode);//오른쪽 자식 노드를 malloc 복사해서 리턴. 복사 안할거면 pNode->pRightchildeNode로 접근하면 되잖아
BinTreeNode peekLeftChildNodeBT(BinTreeNode* pNode);//malloc 없이 값만 반환
BinTreeNode peekRightChildNodeBT(BinTreeNode* pNode);//malloc 없이 값만 반환
void deleteBinTree(BinTree* pBinTree);
void deleteBinTreeNode(BinTreeNode* pNode);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE		1
#define FALSE		0

#endif