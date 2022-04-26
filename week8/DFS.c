#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graphlib.h"
#include "graphlib.c"

void printVertex(int v)
{
	printf("%4d", v);
}


void DFS(graph g, int v1, int color[], void (*func)(int))
{
	// 1 <=> white, 0 <=> gray, -1 <=> black
	
	int adj[6][6];
    for(int i = 0; i < 6; i++)
    for(int j = 0; j < 6; j++)adj[i][j] = -1;
    
	incidentedges(g, v1, adj[v1]);
    
	color[v1] = 0;
	func(v1);
	for(int i = 0; i < 6; i++)
	{
		if(adj[v1][i] >= 0 && color[adj[v1][i]] == 1)
		DFS(g, adj[v1][i], color, func);
	}
	
	color[v1] = -1;
	 
}

int main()
{
   graph g;
   g = creategraph();
   
   int color[6];
   for(int i = 0; i < 6; i++)color[i] = 1;
	
   
   
   addedge(g, 0, 1);
   addedge(g, 1, 2);
   addedge(g, 0, 3);
   addedge(g, 2, 3);
   addedge(g, 2, 4);
   addedge(g, 4, 5);
   printf("DFS: Start from node 1 to node all: \n");

   DFS(g, 1, color, printVertex);
 
   return 0;
   
}
