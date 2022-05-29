#include "graphlinkedlist.h"
#include <stdlib.h>
#include <stdio.h>
#include "arrayqueue.h"

void bfs(LinkedGraph *graph)
{
    ArrayQueue* queue;
    ArrayQueueNode tmp;
    ArrayQueueNode *pop;
    LinkedGraphVertex *push;
    LinkedGraphVertex *edge;
    int         vertexIdx;

    if (!graph)
        return ;
    queue = createArrayQueue(graph->maxVertexCount);
    tmp.data = (graph->pVertex)[0].data.vertexID;
    enqueueAQ(queue, tmp);
    while (!isArrayQueueEmpty(queue))
    {
        pop = dequeueAQ(queue);
        vertexIdx = pop->data;
        printf("%d ->", vertexIdx);
        free(pop);
        pop = NULL;
        if ((graph->pVertex)[vertexIdx].data.visited == 0)
        {
            (graph->pVertex)[vertexIdx].data.visited = 1;
            edge = (graph->pVertex)[vertexIdx].ppAdjEdge;
            while (edge != NULL)
            {
                push = &((graph->pVertex)[edge->data.vertexID]);
                if (push->data.visited == 0)
                {
                    tmp.data = push->data.vertexID;//
                    enqueueAQ(queue, tmp);
                }
                edge = edge->ppAdjEdge;
            }
        }
    }
}

int main()
{
    LinkedGraph *graph;

    // graph = createLinkedGraph(8);
    // for (int i = 0; i < 8 ; i++)
    //     addVertexAG(graph, i);
    // addEdgeAG(graph, 0, 2);
    // addEdgeAG(graph, 0, 1);
    // addEdgeAG(graph, 1, 3);
    // addEdgeAG(graph, 1, 4);
    // addEdgeAG(graph, 2, 5);
    // addEdgeAG(graph, 2, 6);
    // addEdgeAG(graph, 3, 7);
    // addEdgeAG(graph, 4, 5);

    // //displayLinkedGraph(graph);
    
    // printf("Depth First Search\n");
    // dfs(graph);
    
    // deleteLinkedGraph(graph);
    // graph = NULL;
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