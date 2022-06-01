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
int		cycleCheck(t_prim *prim, t_prim temp)
{
	int	*visited;

	visited = calloc(prim->graph->maxVertexCount, sizeof(int));
	if (cycle((prim, visited, temp.toVertex, temp.toVertex)))
	{
		free(visitedAdge);
		return (TRUE);
	}
	free(visitedAdge);
	return (FALSE);
}
