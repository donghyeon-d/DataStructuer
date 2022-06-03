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
		if (prim->visitedAdge[toVertex][i] && visited[i] == 0)
			break ;
	}
	if (cycle(prim, visited, i, temp.toVertex))
	{
		free(visited);
		return (TRUE);
	}
	free(visited);
	return (FALSE);
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

	visited = calloc(prim->graph->maxVertexCount, sizeof(int));
	if (cycle(prim, visited, temp.toVertex, temp.toVertex))
	{
		free(visited);
		return (TRUE);
	}
	free(visited);
	return (FALSE);
}




void cycleCheck()