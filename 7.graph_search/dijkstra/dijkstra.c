#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

// pReturn 에서 가장 작은 값을 갖는 노드 선택
int getMinVertex(ArrayGraph *Graph, int *pReturn, int *visited)
{
    int min;
    int idx;

    min = 2147483647;
    idx = 0;
    for (int i = 0; i < Graph->maxVertexCount; i++)
    {
        if (!visited[i] && pReturn[i] < min)
        {
            min = pReturn[i];
            idx = i;
        }
    }
    return (idx);
}
// 각 노드별로 하나의 
int *dijktra(ArrayGraph *Graph, int start)
{
    int *pReturn;
    int *visited;
    int distance;
    int min_idx;

    pReturn = malloc(sizeof(int) * Graph->maxVertexCount);
    if (pReturn == NULL)
        return (NULL);
    visited = malloc(sizeof(int) * Graph->maxVertexCount);
    if (visited == NULL)
    {
        free(pReturn);
        return (NULL);
    }
    // 시작 노드에서 각 노드에 가는 최단거리 초기화
    for(int i = 0; i < Graph->maxVertexCount; i++)
    {
        if (Graph->ppAdjEdge[start][i] != 0)
            pReturn[i] = Graph->ppAdjEdge[start][i];
        else
            pReturn[i] = 2147483647;
    }
    pReturn[start] = 0;
    visited[start] = USED;
    // 모든 노드를 순회함
    for (int i = 0; i < Graph->maxVertexCount; i++)
    {
        // 현재 배열에서 가장 작은 거리의 노드 고름
        min_idx = getMinVertex(Graph, pReturn, visited);
        distance = pReturn[min_idx];
        visited[min_idx] = USED;
        // 노드에서 갈 수 있는 방향 쭉 보면서 최단거리 값 갱신해줌
        for (int i = 0; i < Graph->maxVertexCount; i++)
        {
            if (visited[i] == NOT_USED && Graph->ppAdjEdge[min_idx][i] && pReturn[i] > distance + Graph->ppAdjEdge[min_idx][i])
                pReturn[i] = distance + Graph->ppAdjEdge[min_idx][i];
        }
    }
    free(visited);
    return (pReturn);
}

int main(void)
{
    ArrayGraph *pGraph;

	pGraph = createArrayGraph(6);
	for (int i = 0; i < 6; i++)
		addVertexAG(pGraph, i);
	addEdgewithWeightAG(pGraph, 0, 1, 1);
	addEdgewithWeightAG(pGraph, 0, 2, 4);
	addEdgewithWeightAG(pGraph, 1, 2, 2);
	addEdgewithWeightAG(pGraph, 2, 3, 1);
	addEdgewithWeightAG(pGraph, 3, 4, 8);
	addEdgewithWeightAG(pGraph, 3, 5, 3);
	addEdgewithWeightAG(pGraph, 4, 5, 4);
	int *d = dijktra(pGraph, 0);
    for (int i = 0; i < 6; i++)
        printf("%d ", d[i]);
	deleteArrayGraph(pGraph);
    free(d);
	system("leaks a.out");
	return (0);
}