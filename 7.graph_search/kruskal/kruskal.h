#ifndef _KRUSKAL_H_
# define _KRUSKAL_H_

# include "../arraygraph.h"

typedef struct 	s_Adge
{
				int fromVertex;
				int toVertex;
				int weight;
}				t_Adge;

typedef struct s_kruskal
{
		ArrayGraph	*graph;
		int			**visitedAdge;
		int			*visitedVertex;
		int			vertexCount;
		t_Adge		*vertexList;
		t_Adge		*resTable;
}		t_kruskal;

t_kruskal	*createkruskal(ArrayGraph *graph);
int		deletekruskal(t_kruskal **kruskal);
void	sortVertexList(t_Adge *vertexList, int len);
t_Adge *createVertexList(t_kruskal *kruskal);
void	kruskalAlgo(t_kruskal *kruskal);
void	displaykruskal(t_kruskal *kruskal);
int find_set(t_kruskal *kruskal, int **set, int vertex);
void	merge_set(t_kruskal *kruskal, int **set, int fromSet, int toSet);
int cycleCheck(t_kruskal *kruskal, int **set, int fromVertex, int toVertex);

#endif