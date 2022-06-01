#ifndef _GRAPH_LinkedGraph_
#define _GRAPH_LinkedGraph_

typedef struct GraphVertexType
{
	int vertexID;		// ��� ID
	int weight;			// ����ġ.
	int visited;
} GraphVertex;

typedef struct LinkedGraphVertexType
{
	GraphVertex data;
	struct LinkedGraphVertexType* ppAdjEdge;
} LinkedGraphVertex;

typedef struct LinkedGraphType
{
	int maxVertexCount;
	int currentVertexCount;
	int graphType;
	LinkedGraphVertex *pVertex;
} LinkedGraph;

LinkedGraph* createLinkedGraph(int maxVertexCount);
LinkedGraph* createArrayDirectedGraph(int maxVertexCount);
void deleteLinkedGraph(LinkedGraph* pGraph);
int isEmptyAG(LinkedGraph* pGraph);
int addVertexAG(LinkedGraph* pGraph, int vertexID);
int addEdgeAG(LinkedGraph* pGraph, int fromVertexID, int toVertexID);
int addEdgewithWeightAG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight);
int checkVertexValid(LinkedGraph* pGraph, int vertexID);
int removeVertexAG(LinkedGraph* pGraph, int vertexID);
int removeEdgeAG(LinkedGraph* pGraph, int fromVertexID, int toVertexID);
void displayLinkedGraph(LinkedGraph* pGraph);

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#define VISITED				1
#define NOT_VISITED			0

#endif