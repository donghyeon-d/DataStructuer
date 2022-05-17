#ifndef _TREE_CALCULATION_
#define _TREE_CALCULATION_

#include "arraybintree.h"
#include "bintree.h"

// duplicate (복사하고 싶은 트리, 어레이 크기)
ArrayBinTree	*dupleArrayBinTree(ArrayBinTree *pbintree, int maxElementCount);
BinTree	*dupleBinTree(BinTree *pbintree);
int	isEqualBintree(BinTree *pBinTreeA, BinTree *pBinTreeB);
int countBintree(BinTree *pBinTree);
BinTree	*copyBinTree(BinTree *pbintree);

#endif