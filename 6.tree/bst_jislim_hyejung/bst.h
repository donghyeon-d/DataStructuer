#ifndef _BST_H_
#define _BST_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef	struct BinSearchTreeNodeType
{
	int								key;
	struct BinSearchTreeNodeType	*pLeftChild;
	struct BinSearchTreeNodeType	*pRightChild;
}									BSTNode;

typedef	struct BinSearchTreeType
{
	BSTNode	*pRootNode;
}	BinSearchTree;

BinSearchTree	*createBinSearchTree();
BSTNode			*insertData(BinSearchTree *bst, int key);
BSTNode			*insertDataNode(BSTNode *node, int key);
BSTNode			*createNewNode(int key);
BSTNode			*deleteData(BinSearchTree *bst, int key);
BSTNode			*deleteDataNode(BSTNode *node, int key);
BSTNode			*minData(BSTNode *node);
BSTNode			*maxData(BSTNode *node);
BSTNode			*search(BinSearchTree *bst, int key);
BSTNode			*searchNode(BSTNode *node, int key);
int				deleteBinSearchTree(BinSearchTree *bst);
int				deleteBSTTreeNode(BSTNode *pNode);
void			preorder(BSTNode *root);
void			inorder(BSTNode *root);
void			postorder(BSTNode *root);

#define	TRUE		1
#define	FALSE		0

#endif