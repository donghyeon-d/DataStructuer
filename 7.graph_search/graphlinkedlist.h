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
LinkedGraph* createLinkedDirectedGraph(int maxVertexCount);
void deleteLinkedGraph(LinkedGraph* pGraph);
int isEmptyLG(LinkedGraph* pGraph);
int addVertexLG(LinkedGraph* pGraph, int vertexID);
int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID);
int addEdgewithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight);
int checkVertexValid(LinkedGraph* pGraph, int vertexID);
int removeVertexLG(LinkedGraph* pGraph, int vertexID);
int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID);
void displayLinkedGraph(LinkedGraph* pGraph);

#endif

#ifndef _COMMON_GRAPH_DEF_
#define _COMMON_GRAPH_DEF_

#define USED				1
#define NOT_USED			0

#define SUCCESS				1
#define FAIL				0

#define TRUE				1
#define FALSE				0

#define GRAPH_UNDIRECTED	1
#define GRAPH_DIRECTED		2
#endif


