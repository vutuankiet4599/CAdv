#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graphlib.h"
#include "graphlib.c"
#include "dllist.h"
#include "dllist.c"
#include <stdbool.h>

void printVertex(int v)
{
	printf("%4d", v);
}
void BFS(graph graph, int v1, int v2, void (*func)(int))
{
   Dllist queue = new_dllist();
   Dllist tmp, node, ptr;
   Jval v;
   bool visited[6];
   int adj[6][6];
   for(int i = 0; i < 6; i++)
   {
	   for(int j = 0; j < 6; j++)
	   adj[i][j] = -1;
   }
   for(int i = 0; i < 6; i++)visited[i] = false;
   dll_append(queue, new_jval_i(v1));

   while(!dll_empty(queue))
   {
	   node = dll_first(queue);
	   v = node->val;
	   func(v.i);
	   if(v.i == v2) break;
	   dll_delete_node(node);
	   if(visited[v.i] == false){
		   
		   visited[v.i] = true;
		   incidentedges(graph, v.i, adj[v.i]);
		   
		   for(int i = 0; i < 6; i++)
		   {
			   if(adj[v.i][i] >= 0 && visited[adj[v.i][i]] == false)
			   {
				    
					dll_append(queue,new_jval_i(adj[v.i][i]));
					   
				   }
			   }
		   }
	   }
   
   printf("\n");
   
}

int main()
{
   graph g;
   g = creategraph();
   int nver = 6;
   int nedge = 6;
   addedge(g, 0, 1);
   addedge(g, 1, 2);
   addedge(g, 0, 3);
   addedge(g, 2, 3);
   addedge(g, 2, 4);
   addedge(g, 4, 5);
   printf("BFS: Start from node 1 to node all: \n");
   BFS(g, 1, -1, printVertex);
   printf("BFS: Start from node 1 to node 3: \n");
   BFS(g, 1, 3, printVertex);
   return 0;
   
}
