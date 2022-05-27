#include "graphlinkedlist.h"
#include <stdio.h>
#include <stdlib.h>

LinkedGraph* createLinkedGraph(int maxVertexCount)
{
    LinkedGraph *rtn;

    if (maxVertexCount <= 0)
        return (NULL);
    rtn = (LinkedGraph *)malloc(sizeof(LinkedGraph));
    if (rtn == NULL)
        return (NULL);
    rtn->maxVertexCount = maxVertexCount;
    rtn->graphType = GRAPH_UNDIRECTED;//1
    rtn->currentVertexCount = 0;
    rtn->pVertex = (LinkedGraphVertex *)malloc(sizeof(LinkedGraphVertex) * maxVertexCount);
    if (rtn->pVertex == NULL)
    {
        free(rtn);
        return (NULL);
    }
    for (int i = 0; i < maxVertexCount; i++)
    {
        (rtn->pVertex)[i].data.vertexID = -1;
        (rtn->pVertex)[i].data.weight = 0;
        (rtn->pVertex)[i].ppAdjEdge = NULL;
    }
    return (rtn);
}

LinkedGraph* createLinkedDirectedGraph(int maxVertexCount)
{
    LinkedGraph *rtn;

    rtn = createLinkedGraph(maxVertexCount);
    rtn->graphType = GRAPH_DIRECTED;//2
    return (rtn);
}

void deleteLinkedGraph(LinkedGraph* pGraph)
{
    LinkedGraphVertex *tmp;
    LinkedGraphVertex *del;

    if (!pGraph)
        return ;
    for (int i = 0; i < pGraph->maxVertexCount; i++)
    {
        tmp = ((pGraph->pVertex)[i]).ppAdjEdge;
        while (tmp)
        {
            del = tmp;
            tmp = tmp->ppAdjEdge;
            free(del);
        }
    }
    free((pGraph->pVertex));
    free(pGraph);
}

int isEmptyLG(LinkedGraph* pGraph)
{
    if (!pGraph)
        return (FALSE);
    if (pGraph->currentVertexCount == 0)
        return (TRUE);
    return (FALSE);
}

int addVertexLG(LinkedGraph* pGraph, int vertexID)
{
    if (!checkVertexValid(pGraph, vertexID))
        return (FALSE);
    (pGraph->pVertex)[vertexID].data.vertexID = vertexID;
    pGraph->currentVertexCount++;
    return (TRUE);
}

int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
    if (!addEdgewithWeightLG(pGraph, fromVertexID, toVertexID, 1))
        return (FALSE);
    return (TRUE);
}

int addEdgewithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
    LinkedGraphVertex *lastNode;
    LinkedGraphVertex *pAdjEdge;
    LinkedGraphVertex *pAdjEdge2;
    
    if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    pAdjEdge = malloc(sizeof(LinkedGraphVertex));
    if (pAdjEdge == NULL)
        return (FALSE);
    pAdjEdge2 = malloc(sizeof(LinkedGraphVertex));
    if (pAdjEdge2 == NULL)
    {
        free(pAdjEdge);
        return (FALSE);
    }
    pAdjEdge->data.vertexID = toVertexID;
    pAdjEdge->data.weight = weight;
    pAdjEdge->ppAdjEdge = NULL;
    pAdjEdge2->data.vertexID = fromVertexID;
    pAdjEdge2->data.weight = weight;
    pAdjEdge2->ppAdjEdge = NULL;
    lastNode = ((pGraph->pVertex)[fromVertexID]).ppAdjEdge;
    if (lastNode == NULL)
        ((pGraph->pVertex)[fromVertexID]).ppAdjEdge = pAdjEdge;
    else
    {
        while (lastNode->ppAdjEdge != NULL)
            lastNode = lastNode->ppAdjEdge;
        lastNode->ppAdjEdge = pAdjEdge;
    }
    if (pGraph->graphType == 1)
    {
        lastNode = ((pGraph->pVertex)[toVertexID]).ppAdjEdge;
        if (lastNode == NULL)
            ((pGraph->pVertex)[toVertexID]).ppAdjEdge = pAdjEdge2;
        else
        {
            while (lastNode->ppAdjEdge != NULL)
                lastNode = lastNode->ppAdjEdge;
            lastNode->ppAdjEdge = pAdjEdge2;
        }
    }
    else
        free(pAdjEdge2);
    return (TRUE);
}

int checkVertexValid(LinkedGraph* pGraph, int vertexID)
{
    if (!pGraph)
        return (FALSE);
    if (vertexID < 0 || vertexID >= pGraph->maxVertexCount)
        return (FALSE);
    return (TRUE);
}

int removeVertexLG(LinkedGraph* pGraph, int vertexID)
{
    LinkedGraphVertex *tmp;
    LinkedGraphVertex *del;

    if (!checkVertexValid(pGraph, vertexID))
        return (FALSE);
    tmp = (pGraph->pVertex)[vertexID].ppAdjEdge;
    while (tmp)
    {
        del = tmp;
        tmp = tmp->ppAdjEdge;
        free(del);
    }
    (pGraph->pVertex)[vertexID].data.vertexID = -1;
    pGraph->currentVertexCount--;
    return (TRUE);
}

int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
    LinkedGraphVertex *del;
    LinkedGraphVertex *tmp;
    
    if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    tmp = (pGraph->pVertex)[fromVertexID].ppAdjEdge;
    if (tmp == NULL)
        return (FALSE);
    while (tmp->ppAdjEdge != NULL && tmp->ppAdjEdge->data.vertexID != toVertexID)
        tmp = tmp->ppAdjEdge;
    if (tmp->ppAdjEdge == NULL)
        return (FALSE);
    del = tmp->ppAdjEdge;
    tmp->ppAdjEdge = del->ppAdjEdge;
    free(del);
    if (pGraph->graphType == 1)
    {
        tmp = pGraph->pVertex[toVertexID].ppAdjEdge;
        while (tmp->ppAdjEdge != NULL && tmp->ppAdjEdge->data.vertexID != fromVertexID)
            tmp = tmp->ppAdjEdge;
        if (tmp->ppAdjEdge == NULL)
            return (FALSE);
        del = tmp->ppAdjEdge;
        tmp->ppAdjEdge = del->ppAdjEdge;
        free(del);
    }
    return (TRUE);
}

void displayLinkedGraph(LinkedGraph* pGraph)
{
    LinkedGraphVertex *tmp;
    int i;

    if (!pGraph)
    {
        printf("Graph is NULL!\n");
        return ;
    }
    
    printf("* Max Vertex Count : %d\n", pGraph->maxVertexCount);

    printf("* Current Vertex Count : %d\n", pGraph->currentVertexCount);

    if (pGraph->graphType == 1)
        printf("* Graph Type : Undirected\n");
    else
        printf("* Graph Type : Directed\n");

    printf("* Vertax valid (Used : i, Not : -1)\n");
    i = -1;
    printf("id   : ");
    while (++i < pGraph->maxVertexCount)
        printf("%d ", i);
    printf("\n");
    i = -1;
    printf("used : ");
    while (++i < pGraph->maxVertexCount)
        printf("%d ", (pGraph->pVertex)[i].data.vertexID);
    printf("\n");

    printf("* Edge\n[from] : (to, weight)\n");
    i = -1;
    while (++i < pGraph->maxVertexCount)
    {
        tmp = (pGraph->pVertex)[i].ppAdjEdge;
        printf("  [%d]  : ", i);
        while (tmp)
        {
            printf("(%d, %d) | ", tmp->data.vertexID, tmp->data.weight);
            tmp = tmp->ppAdjEdge;
        }
        printf("\n");
    }
}

int main()
{
    LinkedGraph *pGraph;

    pGraph = createLinkedGraph(5);
    printf("<<< Init Graph >>> \n");
    displayLinkedGraph(pGraph);
    
    for (int i = 0; i < 5 ; i++)
    {
        addVertexLG(pGraph, i);
    }
    printf("\n<<< Add Vertex >>> \n");
    displayLinkedGraph(pGraph);

    addEdgeLG(pGraph, 1, 4);
    addEdgewithWeightLG(pGraph, 0, 1, 2);
    addEdgewithWeightLG(pGraph, 1, 2, 3);
    addEdgewithWeightLG(pGraph, 2, 3, 4);
    addEdgewithWeightLG(pGraph, 3, 4, 5);
    printf("\n<<< Add Edge >>> \n");
    displayLinkedGraph(pGraph);

    // system("leaks a.out");
}