#include "graphlinkedlist_1.h"
#include "linkedstack.h"
#include "arrayqueue.h"
#include <stdio.h>
#include <stdlib.h>

void dfs(LinkedGraph *graph)
{
	LinkedStack		*stack;
	GraphVertex		vertexNode;
	StackNode		*popNode;
	StackNode		pushNode;
	GraphVertex		*edge;

	if (graph == NULL)
		return ;
	stack = createLinkedStack();
	if (stack == NULL)
		return ;
	vertexNode = (graph->pVertex)[0];
	pushNode.vertexID = vertexNode.vertexID;
	pushNode.pLink = NULL;
	pushLS(stack, pushNode);
	(graph->pVertex)[pushNode.vertexID].visited = 1;
	while (!isLinkedStackEmpty(stack))
	{
		popNode = popLS(stack);
		printf("%d -> ", popNode->vertexID);
		edge = (graph->pVertex)[popNode->vertexID].ppAdjEdge;
		free(edge);//
		while (edge != NULL)
		{
			pushNode.vertexID = edge->vertexID;
			pushNode.pLink = NULL;
			if ((graph->pVertex)[pushNode.vertexID].visited == 0)
			{
				pushLS(stack, pushNode);
				(graph->pVertex)[pushNode.vertexID].visited = 1;
			}
			edge = edge->ppAdjEdge;
		}
	}
}

void bfs(LinkedGraph *graph)
{
	ArrayQueue		*queue;
	ArrayQueueNode	enqueNode;
	ArrayQueueNode	*dequeNode;
	GraphVertex		*edge;

	queue = createArrayQueue(graph->maxVertexCount);
	if (queue == NULL)
		return ;
	enqueNode.vertexID = (graph->pVertex)[0].vertexID;
	enqueueAQ(queue, enqueNode);
	(graph->pVertex)[0].visited = 1;
	while (!isArrayQueueEmpty(queue))
	{
		dequeNode = dequeueAQ(queue);
		printf("%d -> ", dequeNode->vertexID);
		edge = (graph->pVertex)[dequeNode->vertexID].ppAdjEdge;
		free(dequeNode);//
		while (edge)
		{
			enqueNode.vertexID = edge->vertexID;
			if (graph->pVertex[enqueNode.vertexID].visited == 0)
			{
				(graph->pVertex)[edge->vertexID].visited = 1;
				enqueueAQ(queue, enqueNode);
			}
			edge = edge->ppAdjEdge;
		}
	}	
}

int main()
{
    LinkedGraph *graph;

    graph = createLinkedGraph(8);
    for (int i = 0; i < 8 ; i++)
        addVertexLG(graph, i);
    addEdgeLG(graph, 0, 1);
    addEdgeLG(graph, 0, 2);
    addEdgeLG(graph, 1, 3);
    addEdgeLG(graph, 1, 4);
    addEdgeLG(graph, 2, 5);
    addEdgeLG(graph, 2, 6);
    addEdgeLG(graph, 3, 7);
    addEdgeLG(graph, 4, 5);

    // displayLinkedGraph(graph);
    
    printf("Depth First Search\n");
    dfs(graph);
    
    deleteLinkedGraph(graph);
    graph = NULL;
    graph = createLinkedGraph(8);
    for (int i = 0; i < 8 ; i++)
        addVertexLG(graph, i);
    addEdgeLG(graph, 0, 1);
    addEdgeLG(graph, 0, 2);
    addEdgeLG(graph, 1, 3);
    addEdgeLG(graph, 1, 4);
    addEdgeLG(graph, 2, 5);
    addEdgeLG(graph, 2, 6);
    addEdgeLG(graph, 3, 7);
    addEdgeLG(graph, 4, 5);
    printf("\nBreadth First Search\n");
    bfs(graph);
    return (0);
}