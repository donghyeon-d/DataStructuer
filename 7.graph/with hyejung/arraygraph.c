#include "arraygraph.h"
#include <stdio.h>
#include <stdlid.h>

ArrayGraph* createArrayGraph(int maxVertexCount)
{
    ArrayGraph *rtn;

    if (maxVertexCount <= 0)
        return (NULL);
    rtn = (ArrayGraph *)malloc(sizof(ArrayGraph));
    if (rtn == NULL)
        return (NULL);
    rtn->maxVertexCount = maxVertexCount;
    rtn->graphType = 1;
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
        for (int j = 0; j < maxVertexCount; j++)
            (rtn->ppAdjEdge)[i][j] = 0;
    }
    return (rtn);
}

ArrayGraph* createArrayDirectedGraph(int maxVertexCount)
{
    ArrayGraph *rtn;

    if (maxVertexCount <= 0)
        return (NULL);
    rtn = (ArrayGraph *)malloc(sizof(ArrayGraph));
    if (rtn == NULL)
        return (NULL);
    rtn->maxVertexCount = maxVertexCount;
    rtn->graphType = 2;//directed
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
        for (int j = 0; j < maxVertexCount; j++)
            (rtn->ppAdjEdge)[i][j] = 0;
    }
    return (rtn);
}

void deleteArrayGraph(ArrayGraph* pGraph)
{
    if (!pGraph)
        return (NULL);
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
    if (pGraph->graphType = 1)
    {
        (pGraph->ppAdjEdge)[fromVertexID][toVertexID] = 1;
        (pGraph->ppAdjEdge)[toVertexID][fromVertexID] = 1;
    }
    else
        (pGraph->ppAdjEdge)[fromVertexID][toVertexID] = 1;
    return (TRUE);
}
int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight);
{
    if (!pGraph || !checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    if (pGraph->graphType = 1)
    {
        (pGraph->ppAdjEdge)[fromVertexID][toVertexID] = weight;
        (pGraph->ppAdjEdge)[toVertexID][fromVertexID] = weight;
    }
    else
        (pGraph->ppAdjEdge)[fromVertexID][toVertexID] = weight;
    return (TRUE);
}

int checkVertexValid(ArrayGraph* pGraph, int vertexID)
{
    if (!pGraph)
        return (FALSE);
    if (vertexID < 0)
        return (FALSE);
    if (vertexID >= pGraph->maxVertexCount)
        return (FALSE);
    return (TRUE);
}

int removeVertexAG(ArrayGraph* pGraph, int vertexID)
{
    if (!pGraph || !checkVertexValid(pGraph, vertexID))
        return (FALSE);
    if ((pGraph->pVertex)[vertexID] == 1)
    {
        (pGraph->pVertex)[vertexID] = 0;
        return (TRUE);
    }
    else
        return (FALSE);
}

int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
    if (!pGraph || !checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    if (pGraph->graphType = 1)
    {
        (pGraph->ppAdjEdge)[fromVertexID][toVertexID] = 0;
        (pGraph->ppAdjEdge)[toVertexID][fromVertexID] = 0;
    }
    else
        (pGraph->ppAdjEdge)[fromVertexID][toVertexID] = 0;
    return (TRUE);
}

void displayArrayGraph(ArrayGraph* pGraph)
{
    if (!pGraph)
        printf("empty\n");
    for (int i = 0; i < pGraph->maxVertexCount; i++)
    {
        for (int j = 0; j < pGraph->maxVertexCount; j++)
        {
            printf("%d ", pGraph->ppAdjEdge[i][j]);
        }
        printf("\n");
    }
}
