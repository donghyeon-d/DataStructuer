#include "graphlinkedlist.h"
#include "linkedstack.h"
#include "arrayqueue.h"
#include <stdio.h>
#include <stdlib.h>

void dfs(LinkedGraph *graph)
{
    LinkedStack *stack;
    StackNode   tmp;
    StackNode   *pop;
    LinkedGraphVertex *edge;
    int         vertexIdx;
    int         visited[8] = {0,0,0,0,0,0,0,0};

    if (!graph)
        return ;
    stack = createLinkedStack();
    tmp.data = graph->pVertex[0].data.vertexID + '0';
    tmp.pLink = NULL;
    pushLS(stack, tmp);
    while (!isLinkedStackEmpty(stack) && vertexIdx < graph->maxVertexCount)
    {
        pop = popLS(stack);
        vertexIdx = pop->data - '0';
        if (visited[vertexIdx] == 0)
            printf("%d ->", vertexIdx);
        free(pop);
        pop = NULL;
        if (visited[graph->pVertex[vertexIdx].data.vertexID] == 0)
        {
            visited[graph->pVertex[vertexIdx].data.vertexID] = 1;
            edge = graph->pVertex[vertexIdx].ppAdjEdge;
            while (edge != NULL)
            {
                if (visited[edge->data.vertexID] == 0)
                {
                    tmp.data = edge->data.vertexID + '0';
                    tmp.pLink = NULL;
                    pushLS(stack, tmp);
                }
                edge = edge->ppAdjEdge;
            }
        }
    }
}

void bfs(LinkedGraph *graph)
{
    ArrayQueue* queue;
    ArrayQueueNode tmp;
    ArrayQueueNode *pop;
    LinkedGraphVertex *edge;
    int         vertexIdx;
    int         visited[8] = {0,0,0,0,0,0,0,0};

    if (!graph)
        return ;
    queue = createArrayQueue(graph->maxVertexCount);
    tmp.data = graph->pVertex[0].data.vertexID + '0';
    printf("%d ->", tmp.data - '0');
    visited[0] = 1;
    enqueueAQ(queue, tmp);
    while (!isArrayQueueEmpty(queue))
    {
        pop = dequeueAQ(queue);
        vertexIdx = pop->data - '0';
        free(pop);
        pop = NULL;
        edge = graph->pVertex[vertexIdx].ppAdjEdge;
        while (edge != NULL)
        {
            if (visited[edge->data.vertexID] == 0)
            {
                visited[edge->data.vertexID] = 1;
                tmp.data = edge->data.vertexID + '0';
                printf("%d ->", edge->data.vertexID);
                if (!enqueueAQ(queue, tmp))
                    printf("FALSE\n");
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
        addVertexAG(graph, i);
    addEdgeAG(graph, 0, 1);
    addEdgeAG(graph, 0, 2);
    addEdgeAG(graph, 1, 3);
    addEdgeAG(graph, 1, 4);
    addEdgeAG(graph, 2, 5);
    addEdgeAG(graph, 2, 6);
    addEdgeAG(graph, 3, 7);
    addEdgeAG(graph, 4, 5);

    //displayLinkedGraph(graph);
    
    printf("Depth First Search\n");
    dfs(graph);
    
    deleteLinkedGraph(graph);
    graph = NULL;
    graph = createLinkedGraph(8);
    for (int i = 0; i < 8 ; i++)
        addVertexAG(graph, i);
    addEdgeAG(graph, 0, 1);
    addEdgeAG(graph, 0, 2);
    addEdgeAG(graph, 1, 3);
    addEdgeAG(graph, 1, 4);
    addEdgeAG(graph, 2, 5);
    addEdgeAG(graph, 2, 6);
    addEdgeAG(graph, 3, 7);
    addEdgeAG(graph, 4, 5); 
    printf("\nBreadth First Search\n");
    bfs(graph);
    return (0);
}