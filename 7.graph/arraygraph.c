#include <stdio.h>
#include <stdlib.h>
#include "arraygraph.h"

ArrayGraph* createArrayGraph(int maxVertexCount)
{
    ArrayGraph *rtn;

    if (maxVertexCount <= 0)
        return (NULL);
    rtn = (ArrayGraph *)malloc(sizeof(ArrayGraph));
    if (rtn == NULL)
        return (NULL);
    rtn->maxVertexCount = maxVertexCount;
    rtn->graphType = GRAPH_UNDIRECTED;//1
    rtn->currentVertexCount = 0;
    rtn->pVertex = (int *)malloc(sizeof(int) * maxVertexCount);
    if (rtn->pVertex == NULL)
    {
        free(rtn);
        return (NULL);
    }
    for (int i = 0; i < maxVertexCount; i++)
        (rtn->pVertex)[i] = 0;
    rtn->ppAdjEdge = (int **)malloc(sizeof(int *) * maxVertexCount);
    if (rtn->ppAdjEdge == NULL)
    {
        free(rtn->pVertex);
        free(rtn);
        return (NULL);
    }
    for (int i = 0; i < maxVertexCount; i++)
    {
        (rtn->ppAdjEdge)[i] = (int *)malloc(sizeof(int) * maxVertexCount);
        if ((rtn->ppAdjEdge)[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free((rtn->ppAdjEdge)[j]);
            free(rtn->ppAdjEdge);
            free(rtn->pVertex);
            free(rtn);
            return (NULL);
        }
        for (int j = 0; j < maxVertexCount; j++)
            (rtn->ppAdjEdge)[i][j] = 0;
    }
    return (rtn);
}

ArrayGraph* createArrayDirectedGraph(int maxVertexCount)
{
    ArrayGraph *rtn;

    rtn = createArrayGraph(maxVertexCount);
    rtn->graphType = GRAPH_DIRECTED;//2
    return (rtn);
}

void deleteArrayGraph(ArrayGraph* pGraph)
{
    if (!pGraph)
        return ;
    free(pGraph->pVertex);
    for (int i = 0; i < pGraph->maxVertexCount; i++)
    {
        if (pGraph->ppAdjEdge[i])
            free(pGraph->ppAdjEdge[i]);
    }
    free(pGraph->ppAdjEdge);
    free(pGraph);
}

int isEmptyAG(ArrayGraph* pGraph)
{
    if (pGraph == NULL)
        return (FALSE);
    if (pGraph->currentVertexCount == 0)
        return (TRUE);
    else
        return (FALSE);
}

int addVertexAG(ArrayGraph* pGraph, int vertexID)
{
    if (!pGraph || !checkVertexValid(pGraph, vertexID))
        return (FALSE);
    if ((pGraph->pVertex)[vertexID] == 0)
    {
        (pGraph->pVertex)[vertexID] = 1;
        return (TRUE);
    }
    else
        return (FALSE);
}

int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
    if (!pGraph || !checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    (pGraph->ppAdjEdge)[fromVertexID][toVertexID] = 1;
    if (pGraph->graphType == 1)
        (pGraph->ppAdjEdge)[toVertexID][fromVertexID] = 1;
    return (TRUE);
}
int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
    if (!pGraph || !checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    (pGraph->ppAdjEdge)[fromVertexID][toVertexID] = weight;
    if (pGraph->graphType == 1)
        (pGraph->ppAdjEdge)[toVertexID][fromVertexID] = weight;
    return (TRUE);
}

int checkVertexValid(ArrayGraph* pGraph, int vertexID)
{
    if (!pGraph)
        return (FALSE);
    if (vertexID < 0 || vertexID >= pGraph->maxVertexCount)
        return (FALSE);
    return (TRUE);
}

int removeVertexAG(ArrayGraph* pGraph, int vertexID)
{
    if (!pGraph || !checkVertexValid(pGraph, vertexID))
        return (FALSE);
    for (int i = 0; i < pGraph->maxVertexCount; i++)
    {
        (pGraph->ppAdjEdge)[i][vertexID] = 0;
        (pGraph->ppAdjEdge)[vertexID][i] = 0;
    }
    (pGraph->pVertex)[vertexID] = 0;
    return (TRUE);
}

int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
    if (!pGraph || !checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    (pGraph->ppAdjEdge)[fromVertexID][toVertexID] = 0;
    if (pGraph->graphType == 1)
        (pGraph->ppAdjEdge)[toVertexID][fromVertexID] = 0;
    return (TRUE);
}

void displayArrayGraph(ArrayGraph* pGraph)
{
    int i;
    int j;

    if (pGraph == NULL)
    {
        printf("Graph is NULL\n");
        return ;
    }
    printf("* Max Vertex Count : %d\n", pGraph->maxVertexCount);

    printf("* Current Vertex Count : %d\n", pGraph->currentVertexCount);
    
    if (pGraph->graphType == 1)
        printf("* Graph Type : Undirected\n");
    else
        printf("* Graph Type : Directed\n");
    
    printf("* Vertax valid\n");
    i = -1;
    printf("id   : ");
    while (++i < pGraph->maxVertexCount)
        printf("%d ", i);
    printf("\n");
    i = -1;
    printf("used : ");
    while (++i < pGraph->maxVertexCount)
        printf("%d ", (pGraph->pVertex)[i]);
    printf("\n");

    printf("* Edge\n");
    i = -1;
    printf("* ");
    while (++i < pGraph->maxVertexCount)
        printf("%d ", i);
    printf("\n");
    i = -1;
    while (++i < pGraph->maxVertexCount)
    {
        j = -1;
        printf("%d ", i);
        while (++j < pGraph->maxVertexCount)
            printf("%d ", (pGraph->ppAdjEdge)[i][j]);
        printf("\n");
    }
}

int main()
{
    ArrayGraph* pGraph;

    pGraph = createArrayGraph(5);
    printf("Empty : %d (expect = 1)\n", isEmptyAG(pGraph));
    printf("init Graph\n");
    displayArrayGraph(pGraph);
    printf("\n");

    addVertexAG(pGraph, 0);
    addVertexAG(pGraph, 1);
    addVertexAG(pGraph, 2);
    addVertexAG(pGraph, 3);
    
    printf("Check Vertex Valid[4] : %d (expect = 0)\n", checkVertexValid(pGraph, 4));
    printf("\n");

    printf("<<< add edge (0,1) (1,2) >>>\n");
    addEdgeAG(pGraph, 0, 1);
    addEdgeAG(pGraph, 1, 2);
    displayArrayGraph(pGraph);
    printf("\n");

    printf("<<< add edge weight (2,3) 3 >>>\n");
    addEdgewithWeightAG(pGraph, 2, 3, 3);
    displayArrayGraph(pGraph);
    printf("\n");

    printf("<<< remove vertex[0] >>>\n");
    removeVertexAG(pGraph, 0);
    displayArrayGraph(pGraph);
    printf("\n");

    printf("<<< remove edge(1,2) >>>\n");
    removeEdgeAG(pGraph, 1, 2);
    displayArrayGraph(pGraph);
}