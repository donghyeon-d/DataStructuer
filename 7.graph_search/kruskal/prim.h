#ifndef prim_H
# define prim_H

# include "../arraygraph.h"

typedef struct 	s_Adge
{
				int fromVertex;
				int toVertex;
				int weight;
}				t_Adge;

typedef struct s_prim
{
		ArrayGraph	*graph;
		int			**visitedAdge;
		int			*visitedVertex;
		t_Adge		*resTable;
}		t_prim;

t_prim	*createprim(ArrayGraph *graph);

int		primAlgo(t_prim *prim, int vertexID);

t_Adge	minimumAdge(t_prim *prim);

int		cycleCheck(t_prim *prim, t_Adge temp);

void	displayprim(t_prim *prim);

int		deleteprim(t_prim **prim);

#endif
