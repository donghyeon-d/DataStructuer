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
    rtn->graphType = 1;
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

LinkedGraph* createArrayDirectedGraph(int maxVertexCount)
{
    LinkedGraph *rtn;

    if (maxVertexCount <= 0)
        return (NULL);
    rtn = (LinkedGraph *)malloc(sizeof(LinkedGraph));
    if (rtn == NULL)
        return (NULL);
    rtn->maxVertexCount = maxVertexCount;
    rtn->graphType = 2;
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

int isEmptyAG(LinkedGraph* pGraph)
{
    if (!pGraph)
        return (FALSE);
    if (pGraph->currentVertexCount == 0)
        return (TRUE);
    return (FALSE);
}

int addVertexAG(LinkedGraph* pGraph, int vertexID)
{
    LinkedGraphVertex *pVertex;

    if (!pGraph || !checkVertexValid(pGraph, vertexID))
        return (FALSE);
    (pGraph->pVertex)[vertexID].data.vertexID = vertexID;
    pGraph->currentVertexCount++;
    return (TRUE);
}

int addEdgeAG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
    LinkedGraphVertex *tmp;
    LinkedGraphVertex *pAdjEdge;
    LinkedGraphVertex *pAdjEdge2;
    
    if (!pGraph || !checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    pAdjEdge = malloc(sizeof(LinkedGraphVertex));
    if (pAdjEdge == NULL)
        return (FALSE);
    pAdjEdge2 = malloc(sizeof(LinkedGraphVertex));
    if (pAdjEdge2 == NULL)
        return (FALSE);
    pAdjEdge->data.vertexID = toVertexID;
    pAdjEdge->data.weight = 1;
    pAdjEdge->data.visited = 0;
    pAdjEdge->ppAdjEdge = NULL;
    pAdjEdge2->data.vertexID = fromVertexID;
    pAdjEdge2->data.weight = 1;
    pAdjEdge->data.visited = 0;
    pAdjEdge2->ppAdjEdge = NULL;
    tmp = ((pGraph->pVertex)[fromVertexID]).ppAdjEdge;
    if (tmp == NULL)
        ((pGraph->pVertex)[fromVertexID]).ppAdjEdge = pAdjEdge;
    else
    {
        while (tmp->ppAdjEdge != NULL)
            tmp = tmp->ppAdjEdge;
        tmp->ppAdjEdge = pAdjEdge;
    }
    if (pGraph->graphType == 1)
    {
        tmp = ((pGraph->pVertex)[toVertexID]).ppAdjEdge;
        if (tmp == NULL)
            ((pGraph->pVertex)[toVertexID]).ppAdjEdge = pAdjEdge2;
        else
        {
            while (tmp->ppAdjEdge != NULL)
                tmp = tmp->ppAdjEdge;
            tmp->ppAdjEdge = pAdjEdge2;
        }
    }
    else
        free(pAdjEdge2);
    return (TRUE);
}

int addEdgewithWeightAG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
    LinkedGraphVertex *tmp;
    LinkedGraphVertex *pAdjEdge;
    LinkedGraphVertex *pAdjEdge2;
    
    if (!pGraph || !checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    pAdjEdge = malloc(sizeof(LinkedGraphVertex));
    if (pAdjEdge == NULL)
        return (FALSE);
    pAdjEdge2 = malloc(sizeof(LinkedGraphVertex));
    if (pAdjEdge2 == NULL)
        return (FALSE);
    pAdjEdge->data.vertexID = toVertexID;
    pAdjEdge->data.weight = weight;
    pAdjEdge->data.visited = 0;
    pAdjEdge->ppAdjEdge = NULL;
    pAdjEdge2->data.vertexID = fromVertexID;
    pAdjEdge2->data.weight = weight;
    pAdjEdge->data.visited = 0;
    pAdjEdge2->ppAdjEdge = NULL;
    tmp = ((pGraph->pVertex)[fromVertexID]).ppAdjEdge;
    if (tmp == NULL)
        ((pGraph->pVertex)[fromVertexID]).ppAdjEdge = pAdjEdge;
    else
    {
        while (tmp->ppAdjEdge != NULL)
            tmp = tmp->ppAdjEdge;
        tmp->ppAdjEdge = pAdjEdge;
    }
    if (pGraph->graphType == 1)
    {
        tmp = ((pGraph->pVertex)[toVertexID]).ppAdjEdge;
        if (tmp == NULL)
            ((pGraph->pVertex)[toVertexID]).ppAdjEdge = pAdjEdge2;
        else
        {
            while (tmp->ppAdjEdge != NULL)
                tmp = tmp->ppAdjEdge;
            tmp->ppAdjEdge = pAdjEdge2;
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
    if (vertexID < 0)
        return (FALSE);
    if (vertexID >= pGraph->maxVertexCount)
        return (FALSE);
    return (TRUE);
}

int removeVertexAG(LinkedGraph* pGraph, int vertexID)
{
    LinkedGraphVertex *tmp;
    LinkedGraphVertex *del;

    if (!pGraph || checkVertexValid(pGraph, vertexID))
        return (FALSE);
    tmp = (pGraph->pVertex)[vertexID].ppAdjEdge;
    while (tmp)
    {
        del = tmp;
        tmp = tmp->ppAdjEdge;
        free(del);
    }
    (pGraph->pVertex)[vertexID].data.vertexID = -1;
    return (TRUE);
}

int removeEdgeAG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
    LinkedGraphVertex *del;
    LinkedGraphVertex *tmp;
    
    if (!pGraph || !checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    tmp = (pGraph->pVertex)[fromVertexID].ppAdjEdge;
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

    if (!pGraph)
    {
        printf("empty\n");
        return ;
    }
    for (int i = 0; i < pGraph->maxVertexCount; i++)
    {
        tmp = (pGraph->pVertex)[i].ppAdjEdge;
        printf("[%d] ", i);
        while (tmp)
        {
            printf("id : %d, weight : %d | ", tmp->data.vertexID, tmp->data.weight);
            tmp = tmp->ppAdjEdge;
        }
        printf("\n");
    }
}

/*int main()
{
    LinkedGraph *pGraph;

    pGraph = createLinkedGraph(5);
    for (int i = 0; i < 5 ; i++)
    {
        addVertexAG(pGraph, i);
    }
    displayLinkedGraph(pGraph);
    //printf("is empty %d\n", isEmptyAG(pGraph));
    addEdgeAG(pGraph, 1, 4);
    addEdgewithWeightAG(pGraph, 0, 1, 2);
    addEdgewithWeightAG(pGraph, 1, 2, 3);
    addEdgewithWeightAG(pGraph, 2, 3, 4);
    addEdgewithWeightAG(pGraph, 3, 4, 5);
    displayLinkedGraph(pGraph);
}*/