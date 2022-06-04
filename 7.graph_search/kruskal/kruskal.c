#include "kruskal.h"
#include "../arraygraph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

t_kruskal	*createkruskal(ArrayGraph *graph)
{
	t_kruskal *kruskal;
	int n;

	if (!graph)
		return (NULL);
	kruskal = malloc(sizeof(t_kruskal));
	if (!kruskal)
		goto ERROR;
	kruskal->graph = graph;
	n = graph->maxVertexCount;
	kruskal->visitedVertex = calloc(n, sizeof(int));
	if (!kruskal->visitedVertex)
		goto ERROR;
	kruskal->resTable = calloc(n, sizeof(t_Adge));
	if (!kruskal->resTable)
		goto ERROR;
	kruskal->visitedAdge = calloc(n, sizeof(int *));
	if (!kruskal->visitedAdge)
		goto ERROR;
	for (int i = 0; i < n; i++)
	{
		kruskal->visitedAdge[i] = calloc(n, sizeof(int));
		if (!kruskal->visitedAdge[i])
			goto ERROR;
	}
	kruskal->vertexCount = 0;
	return (kruskal);
ERROR:
	deletekruskal(&kruskal);
	return (NULL);
}

void	sortVertexList(t_Adge *vertexList, int len)
{
	int	i;
	int	j;
	t_Adge	tmp;

	if (vertexList == NULL)
		return ;
	i = -1;
	while (++i < len)
	{
		j = -1;
		while (++j + 1 < len)
		{
			if (vertexList[j].weight > vertexList[j + 1].weight)
			{
				tmp = vertexList[j];
				vertexList[j] = vertexList[j + 1];
				vertexList[j + 1] = tmp;
			}
		}
	}
	return ;
}

int find_set(t_kruskal *kruskal, int **set, int vertex)
{
	if (set[kruskal->graph->maxVertexCount][vertex] == 1)
		return (vertex);
	for (int j = 0; j < (kruskal->graph->maxVertexCount + 1); j++)
	{
		if (set[vertex][j] == 1 || set[j][vertex] == 1)
			return (j);
	}
	return (-1);// 유효하지 않은 vertex
}//return = 집합

void	merge_set(t_kruskal *kruskal, int **set, int fromSet, int toSet)
{
	
	for (int i = 0; i < kruskal->graph->maxVertexCount; i++)
	{
		set[fromSet][i] += set[toSet][i];
		set[toSet][i] = 0;
	}
	set[fromSet][toSet] = 1;
	set[kruskal->graph->maxVertexCount][toSet] = 0;
}

int cycleCheck(t_kruskal *kruskal, int **set, int fromVertex, int toVertex)
{
	int fromSet;
	int toSet;

	fromSet = find_set(kruskal, set, fromVertex);
	toSet = find_set(kruskal, set, toVertex);
	if (fromSet == toSet)
		return (TRUE);
	else
		merge_set(kruskal, set, fromSet, toSet);
	return (FALSE);
}

t_Adge *createVertexList(t_kruskal *kruskal)
{
	t_Adge *vertexList;
	int idx;
	int n = kruskal->graph->maxVertexCount;

	vertexList = malloc(sizeof(t_Adge) * (n * (n - 1) / 2));
	if (vertexList == NULL)
		return (NULL);
	for (int i = 0, idx = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			if (i != j && kruskal->graph->ppAdjEdge[i][j] != 0)
			{
				vertexList[idx].fromVertex = i;
				vertexList[idx].toVertex = j;
				vertexList[idx++].weight = kruskal->graph->ppAdjEdge[i][j];
			}
		}
	}
	kruskal->vertexCount = idx;
	sortVertexList(vertexList, idx);
	return (vertexList);
}


int		deletekruskal(t_kruskal **kruskal)
{
	if (*kruskal)
	{
		if ((*kruskal)->visitedVertex)
			free((*kruskal)->visitedVertex);
		if ((*kruskal)->resTable)
			free((*kruskal)->resTable);
		if ((*kruskal)->visitedAdge)
		{
			for (int i = 0; i < (*kruskal)->graph->maxVertexCount; i++)
			{
				if ((*kruskal)->visitedAdge[i])
					free((*kruskal)->visitedAdge[i]);
				else
					break;
			}
			free((*kruskal)->visitedAdge);
		}
		(*kruskal)->graph = NULL;
		free(*kruskal);
		*kruskal = NULL;
	}
	return (SUCCESS);
}

// int cycle(t_kruskal *kruskal, int *visited, int toVertex, int firstVertex)
// {
// 	visited[toVertex] = USED;
// 	if (toVertex == firstVertex)
// 		return (TRUE);
// 	for (int i = 0; i < kruskal->graph->maxVertexCount; i++) 
// 	// 현재 노드에서 유효한 간선 찾기
// 	{
// 		if (kruskal->visitedAdge[toVertex][i] && visited[i] == 0)
// 		{
// 			if (cycle(kruskal, visited, i, firstVertex))
// 				return (TRUE);
// 			if (finish_cycle())
				
// 		}
// 	}
// 	return (FALSE);
// }

// // 닿은 노드에서 kruskal->graph->ppAdjEdge[닿은 노드][temp.to]
// int		cycleCheck(t_kruskal *kruskal, t_Adge temp)
// {
// 	int	*visited;
// 	int	i = -1;

// 	visited = calloc(kruskal->graph->maxVertexCount, sizeof(int));
// 	while (++i < kruskal->graph->maxVertexCount) 
// 	{
// 		if (kruskal->visitedAdge[temp.toVertex][i] && visited[i] == 0)
// 			break ;
// 	}
// 	if (i != kruskal->graph->maxVertexCount && cycle(kruskal, visited, i, temp.toVertex))
// 	{
// 		free(visited);
// 		return (TRUE);
// 	}
// 	free(visited);
// 	return (FALSE);
// }

// int	cycleCheck(t_kruskal *kruskal)
// {
// 	char	**set;
// 	int		max = kruskal->graph->maxVertexCount + 1;

// 	set = (char **)malloc(sizeof(char *) * max);
// 	for (int i = 0, i < max; i++)
// 		set[i] = malloc(sizeof(char) * max);
// 	for (int i = 0, i < max; i++)
// 	{
// 		for (int j = 0; j < max; j++)
// 			set[i][j] = 0;
// 	}
// 	for (int i = 0, i < max; i++)
// 		set[max - 1][i] = 1;
// }


void	kruskalAlgo(t_kruskal *kruskal)
{
	int	idx;
	t_Adge temp;
	int **set;

	set = malloc(sizeof(int *) * (kruskal->graph->maxVertexCount + 1));
	for (int i = 0; i < (kruskal->graph->maxVertexCount + 1); i++)
		set[i] = calloc(kruskal->graph->maxVertexCount, sizeof(int));
	for (int i = 0; i < (kruskal->graph->maxVertexCount + 1); i++)
		set[kruskal->graph->maxVertexCount][i] = 1;
	idx = 0;
	for (int i = 0; i < kruskal->vertexCount; i++)
	{
		if (!cycleCheck(kruskal, set, kruskal->vertexList[i].fromVertex, kruskal->vertexList[i].toVertex))
		{
			kruskal->resTable[idx++] = kruskal->vertexList[i];
			temp = kruskal->vertexList[i];
			kruskal->visitedAdge[temp.fromVertex][temp.toVertex] = USED;
		}
	}
}

void	displaykruskal(t_kruskal *kruskal)
{
	int sum = 0;

	for (int i = 0; i < kruskal->graph->maxVertexCount - 1; i++)
	{
		printf("from : %d -> to : %d [%d]\n", kruskal->resTable[i].fromVertex, kruskal->resTable[i].toVertex, kruskal->resTable[i].weight);
		sum += kruskal->resTable[i].weight;
	}
	printf("total weight : %d\n", sum);
}

int main(void)
{
	t_kruskal *kruskal;
	ArrayGraph *pGraph;

	pGraph = createArrayGraph(6);
	kruskal = createkruskal(pGraph);
	for (int i = 0; i < 6; i++)
		addVertexAG(pGraph, i);
	addEdgewithWeightAG(pGraph, 0, 1, 4);
	addEdgewithWeightAG(pGraph, 0, 2, 3);
	addEdgewithWeightAG(pGraph, 1, 2, 2);
	addEdgewithWeightAG(pGraph, 2, 3, 1);
	addEdgewithWeightAG(pGraph, 3, 4, 1);
	addEdgewithWeightAG(pGraph, 3, 5, 5);
	addEdgewithWeightAG(pGraph, 4, 5, 6);
	kruskal->vertexList = createVertexList(kruskal);
	kruskalAlgo(kruskal);
	displaykruskal(kruskal);
	deletekruskal(&kruskal);
	deleteArrayGraph(pGraph);
	// system("leaks a.out");
	return (0);
}