#include <stdlib.h>
#include <stdio.h>
#include "arraygraph.h"

ArrayGraph* createArrayGraph(int maxVertexCount)
{
    ArrayGraph  *newArrayGraph;
    int         i;
    int         j;

    if (maxVertexCount <= 0)
        return (NULL);
    newArrayGraph = malloc(sizeof(ArrayGraph));
    if (newArrayGraph == NULL)
        return (NULL);
    newArrayGraph->maxVertexCount = maxVertexCount;
    newArrayGraph->currentVertexCount = 0;
    newArrayGraph->graphType = GRAPH_UNDIRECTED;//1
    newArrayGraph->ppAdjEdge = malloc(sizeof(int *) * maxVertexCount);
    if (newArrayGraph->ppAdjEdge == NULL)
    {
        free(newArrayGraph);
        return (NULL);
    }
    i = -1;
    while (++i < maxVertexCount)
        (newArrayGraph->ppAdjEdge)[i] = NULL;
    newArrayGraph->pVertex = malloc(sizeof(int) * maxVertexCount);
    if (newArrayGraph->pVertex == NULL)
    {
        free(newArrayGraph->ppAdjEdge);
        free(newArrayGraph);
        return (NULL);
    }
    i = -1;
    while (++i < maxVertexCount)
        (newArrayGraph->pVertex)[i] = NOT_USED;
    i = -1;
    while (++i < maxVertexCount)
    {
        j = -1;
        (newArrayGraph->ppAdjEdge)[i] = malloc(sizeof(int) * maxVertexCount);
        if ((newArrayGraph->ppAdjEdge)[i] == NULL)
        {
            i = -1;
            while((newArrayGraph->ppAdjEdge)[++i] != NULL)
                free((newArrayGraph->ppAdjEdge)[i]);
            free(newArrayGraph->ppAdjEdge);
            free(newArrayGraph);
            return (NULL);
        }
        while (++j < maxVertexCount)
            (newArrayGraph->ppAdjEdge)[i][j] = 0;
    }
    return (newArrayGraph);
}

ArrayGraph* createArrayDirectedGraph(int maxVertexCount)
{
    ArrayGraph  *newArrayGraph;

    if (maxVertexCount <= 0)
        return (NULL);
    newArrayGraph = createArrayGraph(maxVertexCount);
    if (newArrayGraph == NULL)
        return (NULL);
    newArrayGraph->graphType = GRAPH_DIRECTED;//2
    return (newArrayGraph);
}

void deleteArrayGraph(ArrayGraph* pGraph)
{
    int i;
    int maxCount;

    i = -1;
    maxCount = pGraph->maxVertexCount;
    free(pGraph->pVertex);
    while (++i < maxCount)
        free((pGraph->ppAdjEdge)[i]);
    free(pGraph->ppAdjEdge);
    free(pGraph);
}

int isEmptyAG(ArrayGraph* pGraph)
{
    if (pGraph == NULL)
        return (ERROR);
    if (pGraph->currentVertexCount == 0)
        return (TRUE);
    return (FALSE);
}

int addVertexAG(ArrayGraph* pGraph, int vertexID)
{
    if (pGraph == NULL || pGraph->maxVertexCount <= vertexID)
        return (ERROR);
    if (pGraph->maxVertexCount == pGraph->currentVertexCount)
        return (FAIL);
    (pGraph->pVertex)[vertexID] = USED;
    pGraph->currentVertexCount++;
    return (SUCCESS);
}

int checkVertexValid(ArrayGraph* pGraph, int vertexID)
{
    if (pGraph == NULL || (pGraph->pVertex)[vertexID] == NOT_USED)
        return (FALSE);
    return (TRUE);
}

int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
    if (pGraph == NULL || pGraph->maxVertexCount <= fromVertexID || pGraph->maxVertexCount <= toVertexID)
        return (ERROR);
    if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FAIL);
    (pGraph->ppAdjEdge)[fromVertexID][toVertexID] = 1;
    if (pGraph->graphType == GRAPH_UNDIRECTED)
        (pGraph->ppAdjEdge)[toVertexID][fromVertexID] = 1;
    return (SUCCESS);
}

int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
    if (pGraph == NULL || pGraph->maxVertexCount <= fromVertexID || pGraph->maxVertexCount <= toVertexID)
        return (ERROR);
    if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FAIL);
    (pGraph->ppAdjEdge)[fromVertexID][toVertexID] = weight;
    if (pGraph->graphType == GRAPH_UNDIRECTED)
        (pGraph->ppAdjEdge)[toVertexID][fromVertexID] = weight;
    return (SUCCESS);
}

int removeVertexAG(ArrayGraph* pGraph, int vertexID)
{
    int i;

    if (pGraph == NULL || pGraph->maxVertexCount <= vertexID)
        return (ERROR);
    if (pGraph->currentVertexCount == 0 || !checkVertexValid(pGraph, vertexID))
        return (FAIL);
    (pGraph->pVertex)[vertexID] = NOT_USED;
    i = -1;
    while (++i < pGraph->maxVertexCount)
        (pGraph->ppAdjEdge)[vertexID][i] = 0;
    i = -1;
    while (++i < pGraph->maxVertexCount)
        (pGraph->ppAdjEdge)[i][vertexID] = 0;
    pGraph->currentVertexCount--;
    return (SUCCESS);
}

int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
    if (pGraph == NULL || pGraph->maxVertexCount <= fromVertexID || pGraph->maxVertexCount <= toVertexID)
        return (ERROR);
    if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FAIL);
    (pGraph->ppAdjEdge)[fromVertexID][toVertexID] = 0;
    if (pGraph->graphType == GRAPH_UNDIRECTED)
        (pGraph->ppAdjEdge)[toVertexID][fromVertexID] = 0;
    return (SUCCESS);
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
    addVertexAG(pGraph, 0);
    addVertexAG(pGraph, 1);
    addVertexAG(pGraph, 2);
    addVertexAG(pGraph, 3);
    
    printf("Check Vertex Valid[4] : %d (expect = 0)\n", checkVertexValid(pGraph, 4));


    addEdgeAG(pGraph, 0, 1);
    addEdgeAG(pGraph, 1, 2);
    addEdgewithWeightAG(pGraph, 2, 3, 3);
    displayArrayGraph(pGraph);

    removeVertexAG(pGraph, 0);
    displayArrayGraph(pGraph);

    removeEdgeAG(pGraph, 1, 2);
    displayArrayGraph(pGraph);
}