#include "linkeddeque.h"

int	main(void)
{
	LinkedDeque	*pDeque = createLinkedDeque();
	DequeNode	node;
	node.data = 50;
	// printf("check : %d\n", peekFront(pDeque)); // 0 나와야 정상
	printf("%d\n", pDeque->currentElementCount);
	for (int i = 0; i < 5; i++)
	{
		// printf("%d\n", insertFront(pDeque, node));
		printf("%d\n", insertRear(pDeque, node));
		node.data -= 10;
	}
	printf("crnt : %d\n", pDeque->currentElementCount);
	printf("-----------------------------\n");
	DequeNode	*pp = pDeque->pFrontNode;
	// DequeNode	*pp = pDeque->pRearNode;
	for (int i = 0; i < 5; i++)
	{
		printf("data : %d\n", pp->data);
		pp = pp->pRLink;
		// pp = pp->pLLink;
	}
	printf("crnt : %d\n", pDeque->currentElementCount);
	printf("-----------------------------\n");
	for (int i = 0; i < 5; i++)
	{
		// printf("data : %d\n", pDeque->pFrontNode->data);
		// deleteFront(pDeque);
		printf("data : %d\n", pDeque->pRearNode->data);
		deleteRear(pDeque);
	}
	// printf("data : %d\n", pDeque->pFrontNode->data); // 여기서 segfault가 나와야 정상. 굿 잘 나옴.
	// printf("data : %d\n", pDeque->pRearNode->data); // 여기서 segfault가 나와야 정상. 굿 잘 나옴.
	printf("crnt : %d\n", pDeque->currentElementCount);
}