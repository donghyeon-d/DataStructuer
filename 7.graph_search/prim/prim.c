#include "prim.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	t_prim *prim;
	ArrayGraph *graph;

	graph = createArrayGraph(5);
	prim = createprim(graph);
	deleteprim(&prim);
	deleteArrayGraph(graph);
	system("leaks a.out");
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
	prim->resTable = calloc(graph->maxVertexCount, sizeof(int));
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
	for (int i = 0; i < prim->graph->maxVertexCount; i++)
	{
		for (int j = 0; j < prim->graph->maxVertexCount; j++)
		{
			if (prim->visitedVertex[j] == USED)
			{
				temp = minimumAdge(prim);
				prim->visitedVertex[temp.toVertex] = USED;
				prim->visitedAdge[temp.fromVertex][temp.toVertex] = USED;
				prim->visitedAdge[temp.toVertex][temp.fromVertex] = USED;
				resTable[i] = temp;
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
			for (int j = 0; i < prim->graph->maxVertexCount; j++)
			{
				if (temp.weight > prim->graph->ppAdjEdge[i][j])
				{
					temp.weight = prim->graph->ppAdjEdge[i][j])
					temp.fromVertex = i;
					temp.toVertex = j;
					prim->visitedAdge[i][j] = USED;
					if (circleCheck(prim, temp))
					{
						prim->visitedAdge[i][j] = NOT_USED;
						temp = temp2;
					}
					temp2 = temp;
				}
			}
		}
	}
	return (temp);
}

// 재귀함수
int cycle(t_prim *prim, int *visited, int toVertex)
{
	visited[toVertex] = USED;
	for (int i = 0; i < prim->graph->maxVertexCount; i++) 
	// 현재 노드에서 유효한 간선 찾기
	{
		if (prim->visitedAdge[toVertex][i])
			cycle(prim, visited, i);
		if ()
			return (TRUE);
	}
	return (FALSE);
}

int		cycleCheck(t_prim *prim, t_prim temp)
{
	int	*visited;

	visited = calloc(prim->graph->maxVertexCount, sizeof(int));
	return (cycle(prim, visited, temp.toVertex));
}

void	displayprim(t_prim *prim);

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