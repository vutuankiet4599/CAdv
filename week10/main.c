#include "weightedGraphlib.h"
#include "dllist.h"
#include <stdio.h>
#include <string.h>

double dijikstra(Graph graph, int start, int stop, int *path, int *length){
	double total, distance[1000];
	int min, id, i, n, neighbor, position, previous[1000], output[1000], temp[1000];
	Dllist queue, shortest, node;
	
	for(i = 0; i < 100; i++){
		distance[i] = INFINITIVE_VALUE;
	}
	
	distance[start] = 0;
	previous[start] = start;
	
	queue = new_dllist();
	dll_append(queue, new_jval_i(start));
	
	while(!dll_empty(queue)){
		
		min = INFINITIVE_VALUE;
		
		dll_traverse(node, queue){
			id = jval_i(node->val);
			if(min > distance[id]){
				min = distance[id];
				shortest = node;
			}
		}
		
		id = jval_i(shortest->val);
		dll_delete_node(shortest);
			
		if(id == stop)break;
			
		n = outdegree(graph, id, output);
		for(i = 0; i < n; i++){
			neighbor = output[i];
			if(distance[neighbor] > distance[id] + getEdgeValue(graph, id, neighbor)){
				distance[neighbor] = distance[id] + getEdgeValue(graph, id, neighbor);
				previous[neighbor] = id;
				dll_append(queue, new_jval_i(neighbor));
			}
		}
	}
	
	total = distance[stop];
	if(total != INFINITIVE_VALUE){
		temp[0] = stop;
		position = 1;
		while(stop != start){
			stop = previous[stop];
			temp[position] = stop;
			position += 1;
		}
		for(i = position - 1; i >= 0; i --){
            path[position - i - 1] = temp[i];
		}
        *length = position;
	}
	
	return total;
}

int main(){
  int i, n, output[100];
  Graph g = createGraph();
  char s1[] = "station 1";
  char s2[] = "station 2";
  char s3[] = "station 3";

  addVertex(g,1,s1);
  addVertex(g,2,s2);
  addVertex(g,3,s3);
  
  addEdge(g,1,2,1.2);
  addEdge(g,1,3,3.4);
  int path[100], length;
  memset(path, 0, sizeof(path));
 
  double total;
  total = dijikstra(g, 1, 2, path, &length);
  
  printf("%lf\n",total);
  int j = 0;
  while(path[j] != 0){
	  printf("%s ", getVertex(g, path[j]));
	  j++;
  }
 
  printf("\n");
   
  printf("%d\n", length);
  
  dropGraph(g);
}
