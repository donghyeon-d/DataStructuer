#ifndef _BS_TREE_
#define _BS_TREE_

#include "bintree.h"

BinTreeNode*    insertNodeBST(BinTree* pBinTree, BinTreeNode element);
void            deleteBSTNode(BinTree* pBinTree, BinTreeNode element);
BinTreeNode*    searchBSTNode(BinTree* pBinTree, BinTreeNode element);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE    1
#define FALSE   0

#endif
