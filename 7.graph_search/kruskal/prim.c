#include "prim.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	t_prim *prim;
	ArrayGraph *pGraph;

	pGraph = createArrayGraph(6);
	prim = createprim(pGraph);
	for (int i = 0; i < 6; i++)
		addVertexAG(pGraph, i);
	addEdgewithWeightAG(pGraph, 0, 1, 4);
	addEdgewithWeightAG(pGraph, 0, 2, 3);
	addEdgewithWeightAG(pGraph, 1, 2, 2);
	addEdgewithWeightAG(pGraph, 2, 3, 1);
	addEdgewithWeightAG(pGraph, 3, 4, 1);
	addEdgewithWeightAG(pGraph, 3, 5, 5);
	addEdgewithWeightAG(pGraph, 4, 5, 6);
	primAlgo(prim, 1);
	displayprim(prim);
	deleteprim(&prim);
	deleteArrayGraph(pGraph);
	// system("leaks a.out");
	return (0);
}

t_prim	*createprim(ArrayGraph *graph)
{
	t_prim *prim;

	if (!graph)
		return (NULL);
	prim = malloc(sizeof(t_prim));
	if (!prim)
		goto ERROR;
	prim->graph = graph;
	prim->visitedVertex = calloc(graph->maxVertexCount, sizeof(int));
	if (!prim->visitedVertex)
		goto ERROR;
	prim->resTable = calloc(graph->maxVertexCount, sizeof(t_Adge));
	if (!prim->resTable)
		goto ERROR;
	prim->visitedAdge = calloc(graph->maxVertexCount, sizeof(int *));
	if (!prim->visitedAdge)
		goto ERROR;
	for (int i = 0; i < graph->maxVertexCount; i++)
	{
		prim->visitedAdge[i] = calloc(graph->maxVertexCount, sizeof(int));
		if (!prim->visitedAdge[i])
			goto ERROR;
	}
	return (prim);
ERROR:
	deleteprim(&prim);
	return (NULL);
}

int		primAlgo(t_prim *prim, int vertexID)
{
	t_Adge	temp;

	prim->visitedVertex[vertexID] = USED;
	for (int i = 0; i < prim->graph->maxVertexCount - 1; i++)
	{
		for (int j = 0; j < prim->graph->maxVertexCount; j++)
		{
			if (prim->visitedVertex[j] == USED)
			{
				temp = minimumAdge(prim);
				prim->visitedVertex[temp.toVertex] = USED;
				prim->visitedAdge[temp.fromVertex][temp.toVertex] = USED;
				prim->visitedAdge[temp.toVertex][temp.fromVertex] = USED;
				prim->resTable[i] = temp;
				break ;
			}
		}
	}
	return (0);
}

t_Adge	minimumAdge(t_prim *prim)
{
	t_Adge	temp;
	t_Adge	temp2;

	temp.weight = 2147483647;
	for (int i = 0; i < prim->graph->maxVertexCount; i++)
	{
		if (prim->visitedVertex[i])
		{
			for (int j = 0; j < prim->graph->maxVertexCount; j++)
			{
				if (prim->graph->ppAdjEdge[i][j] && temp.weight > prim->graph->ppAdjEdge[i][j] && !prim->visitedAdge[i][j])
				{
					if (temp.weight != 2147483647)
						prim->visitedAdge[temp2.fromVertex][temp2.toVertex] = NOT_USED;
					temp.weight = prim->graph->ppAdjEdge[i][j];
					temp.fromVertex = i;
					temp.toVertex = j;
					prim->visitedAdge[i][j] = USED;
					if (cycleCheck(prim, temp))
					{
						prim->visitedAdge[i][j] = NOT_USED;
						temp = temp2;
						temp.weight = 2147483647;
					}
					temp2 = temp;
				}
			}
		}
	}
	return (temp);
}

int cycle(t_prim *prim, int *visited, int toVertex, int firstVertex)
{
	visited[toVertex] = USED;
	if (toVertex == firstVertex)
		return (TRUE);
	for (int i = 0; i < prim->graph->maxVertexCount; i++) 
	// 현재 노드에서 유효한 간선 찾기
	{
		if (prim->visitedAdge[toVertex][i] && visited[i] == 0)
		{
			if (cycle(prim, visited, i, firstVertex))
				return (TRUE);
		}
	}
	return (FALSE);
}

// 닿은 노드에서 prim->graph->ppAdjEdge[닿은 노드][temp.to]
int		cycleCheck(t_prim *prim, t_Adge temp)
{
	int	*visited;
	int	i = -1;

	visited = calloc(prim->graph->maxVertexCount, sizeof(int));
	while (++i < prim->graph->maxVertexCount) 
	{
		if (prim->visitedAdge[temp.toVertex][i] && visited[i] == 0)
			break ;
	}
	if (i != prim->graph->maxVertexCount && cycle(prim, visited, i, temp.toVertex))
	{
		free(visited);
		return (TRUE);
	}
	free(visited);
	return (FALSE);
}

void	displayprim(t_prim *prim)
{
	int sum = 0;

	for (int i = 0; i < prim->graph->maxVertexCount - 1; i++)
	{
		printf("from : %d -> to : %d\n", prim->resTable[i].fromVertex, prim->resTable[i].toVertex);
		sum += prim->resTable[i].weight;
	}
	printf("total weight : %d\n", sum);
}

int		deleteprim(t_prim **prim)
{
	if (*prim)
	{
		if ((*prim)->visitedVertex)
			free((*prim)->visitedVertex);
		if ((*prim)->resTable)
			free((*prim)->resTable);
		if ((*prim)->visitedAdge)
		{
			for (int i = 0; i < (*prim)->graph->maxVertexCount; i++)
			{
				if ((*prim)->visitedAdge[i])
					free((*prim)->visitedAdge[i]);
				else
					break;
			}
			free((*prim)->visitedAdge);
		}
		(*prim)->graph = NULL;
		free(*prim);
		*prim = NULL;
	}
	return (SUCCESS);
}