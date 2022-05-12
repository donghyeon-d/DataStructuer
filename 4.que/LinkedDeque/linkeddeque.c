#include "linkeddeque.h"

LinkedDeque	*createLinkedDeque()
{
	LinkedDeque	*rt_pDeque;

	rt_pDeque = malloc(sizeof(LinkedDeque));
	if (!rt_pDeque)
		return (NULL);
	rt_pDeque->pFrontNode = NULL;
	rt_pDeque->pRearNode = NULL;
	rt_pDeque->currentElementCount = 0;
	return (rt_pDeque);
}

int insertFront(LinkedDeque *pDeque, DequeNode element)
{
	DequeNode	*node;

	if (!pDeque)
		return (FALSE);
	node = malloc(sizeof(DequeNode));
	if (!node)
		return (FALSE);
	node->data = element.data;
	if (isLinkedDequeEmpty(pDeque))
	{
		node->pRLink = NULL;
		node->pLLink = NULL;
		pDeque->pFrontNode = node;
		pDeque->pRearNode = node;
	}
	else
	{
		node->pRLink = pDeque->pFrontNode;
		node->pLLink = NULL;
		pDeque->pFrontNode->pLLink = node;
		if (pDeque->currentElementCount == 1)
			pDeque->pRearNode = pDeque->pFrontNode;
		pDeque->pFrontNode = node;
	}
	pDeque->currentElementCount += 1;
	return (TRUE);
}

int insertRear(LinkedDeque *pDeque, DequeNode element)
{
	DequeNode	*node;

	if (!pDeque)
		return (FALSE);
	// 위 함수에서 처리. 잘 되니까
	if (isLinkedDequeEmpty(pDeque))
	{
		if (insertFront(pDeque, element))
			return (TRUE);
		else
			return (FALSE);
	}
	node = malloc(sizeof(DequeNode));
	if (!node)
		return (FALSE);
	node->data = element.data;
	node->pRLink = NULL;
	node->pLLink = pDeque->pRearNode;
	pDeque->pRearNode->pRLink = node;
	pDeque->pRearNode = node;
	pDeque->currentElementCount += 1;
	return (TRUE);
}
DequeNode	*deleteFront(LinkedDeque *pDeque)
{
	DequeNode	*rt_node;

	if (!pDeque || isLinkedDequeEmpty(pDeque))
		return (FALSE);
	rt_node = pDeque->pFrontNode;
	pDeque->pFrontNode = pDeque->pFrontNode->pRLink;
	if (pDeque->pFrontNode != NULL)
		pDeque->pFrontNode->pLLink = NULL;
	pDeque->currentElementCount -= 1;
	return (rt_node);
}

DequeNode	*deleteRear(LinkedDeque *pDeque)
{
	DequeNode	*rt_node;

	if (!pDeque || isLinkedDequeEmpty(pDeque))
		return (FALSE);
	rt_node = pDeque->pRearNode;
	pDeque->pRearNode = pDeque->pRearNode->pLLink;
	if (pDeque->pRearNode != NULL)
		pDeque->pRearNode->pRLink = NULL;
	pDeque->currentElementCount -= 1;
	return (rt_node);
}
// peek할 때 주소를 그대로 넘겨주지 말고, 따로 복사해서 넘겨줘야 값 변경이 안일어난다.
DequeNode	*peekFront(LinkedDeque *pDeque)
{
	DequeNode	*rt_node;

	if (!pDeque || isLinkedDequeEmpty(pDeque))
		return (FALSE);
	rt_node = malloc(sizeof(DequeNode));
	if (rt_node == NULL)
		return (NULL);
	rt_node->data = pDeque->pFrontNode->data;	
	return (rt_node);
}

DequeNode	*peekRear(LinkedDeque *pDeque)
{
	DequeNode	*rt_node;

	if (!pDeque || isLinkedDequeEmpty(pDeque))
		return (FALSE);
	rt_node = malloc(sizeof(DequeNode));
	if (rt_node == NULL)
		return (NULL);
	rt_node->data = pDeque->pRearNode->data;
	return (rt_node);
}
void	deleteLinkedDeque(LinkedDeque *pDeque)
{
	DequeNode	*node;
	DequeNode	*next;

	if (!pDeque || !isLinkedDequeEmpty(pDeque))
		return ;
	node = pDeque->pFrontNode;
	while (node)
	{
		next = node->pRLink;
		free (node);
		node = next;
	}
	free (pDeque);
}

int	isLinkedDequeEmpty(LinkedDeque *pDeque)
{
	// if (!pDeque || pDeque->currentElementCount != 0) 이건 왜 안될까..?
	if (!pDeque)
		return (FALSE);
	if (pDeque->currentElementCount == 0)
		return (TRUE);
	else
		return (FALSE);
}
