#include "bst.h"

int main()
{
	BinSearchTree	*bst;

	bst = createBinSearchTree();
	insertData(bst, 30);
	insertData(bst, 20);
	insertData(bst, 40);
	insertData(bst, 10);
	insertData(bst, 24);
	insertData(bst, 34);
	insertData(bst, 22);
	insertData(bst, 14);
	insertData(bst, 6);
	insertData(bst, 46);
	insertData(bst, 48);
	insertData(bst, 42);
	insertData(bst, 25);
	insertData(bst, 32);
	insertData(bst, 35);

	deleteData(bst, 20);
	printf("==========  del(20) 실행  ==========\n");
	printf("예상 결과\n30 22 10 6 14 24 25 40 34 32 35 46 42 48\n");
	printf("실제 결과\n");
	inorder(bst->pRootNode);
	printf("\n\n");
	deleteData(bst, 30);
	printf("==========  del(30) 실행  ==========\n");
	printf("예상 결과\n32 22 10 6 14 24 25 40 34 35 46 42 48\n");
	printf("실제 결과\n");
	inorder(bst->pRootNode);
	printf("\n\nsearch 42key : %d\n", search(bst, 42)->key);
	deleteBinSearchTree(bst);
	
	// system("leaks a.out | grep leaked");
}