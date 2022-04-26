#include <stdio.h>
#include "directedGraphlib.h"
#include "directedGraphlib.c"
#include "fields.h"
#include "dllist.h"

void printVertices(char *s){
	printf("%s ", s);
}

int DAG(Graph graph){
	JRB vertex;
	JRB node;
	int visited[1000];
	Dllist queue, temp;
	int i, n, output[100];
	jrb_traverse(vertex, graph->vertices){
		memset(visited, 0, sizeof(visited));
		queue = new_dllist();
        dll_append(queue, vertex->key);
        
        while(!dll_empty(queue)){
			temp = dll_first(queue);
            int value = jval_i(temp->val);
            dll_delete_node(temp);
            if(visited[value] == 0){
				visited[value] = 1;
				n = outdegree(graph, value, output);
				int outkey;
				for(i = 0; i < n; i++){
					outkey = output[i];
					if(outkey == jval_i(vertex->key)){
						free_dllist(queue);
						return 0;
					}
					
					if(visited[outkey] == 0){
						dll_append(queue, new_jval_i(outkey));
					}
				}
			}
		}
		free_dllist(queue);
	}
	return 1;
}


int readFromFile(Graph g, char *filename){
	IS is;
	is = new_inputstruct(filename);
	Dllist list = new_dllist();
	Dllist ptr ;
	
	int nVer = 0;
	int count;
	char *s ;
	char *name[50];
	int m, n;
	
	while(get_line(is) >= 0){
		int count = 0;
		if(is->NF > 1){
			s = strdup(is->fields[1]);
			dll_traverse(ptr, list){
				if(strcmp(s, ptr->val.s) == 0){
					count ++;
				}
			}
			if(count == 0){
				dll_append(list, new_jval_s(s));
			}
		}
	}
	
	dll_traverse(ptr, list){
		name[nVer] = strdup(ptr->val.s);
		nVer ++;
	}
	
	for(int i = 0; i <nVer; i++){
		addVertex(g, i, name[i]);
	}

	free_dllist(list);
	jettison_inputstruct(is);
	
	IS is1;
	is1 = new_inputstruct(filename);
	
	while(get_line(is1) >= 0){
		if(is1->NF > 1){
			if(strcmp(is1->fields[0], "CLASS") == 0){
				for(m = 0; m < nVer; m++){
					if(strcmp(is->fields[1], name[m]) == 0){
						break;
					}
				}
			}
			
			if(strcmp(is1->fields[0], "PREREQ") == 0){
				for(n = 0; n < nVer; n++){
					if(strcmp(is->fields[1], name[n]) == 0){
						addEdge(g, n, m);
					}
				}
			}
		}	
	}
	
	jettison_inputstruct(is1);
	return nVer;
}

void topology(Graph g, int nVer, void (*func)(char*)){
	
	Dllist queue = new_dllist();
	Dllist node, ptr;
	int count;
	int inde[nVer] ;
	Jval v;
	int inVertex[nVer][nVer];
	
	for(int i = 0; i < nVer; i++){
		inde[i] = indegree(g, i, inVertex[i]);
		if(inde[i] == 0){
			dll_append(queue, new_jval_i(i));
		}
	}
	
	while(!dll_empty(queue)){
	   node = dll_first(queue);
	   v = node->val;
	   dll_delete_node(node);
	   func(getVertex(g, v.i));
	   for(int i = 0; i < nVer; i++){	 
		   
		   if(hasEdge(g, v.i, i) == 1 && inde[i] != 0){
			   inde[i] = inde[i] - 1;
			   
			   if(inde[i] == 0){
				   dll_append(queue, new_jval_i(i));
		       }
		   }
	   }
	}
	printf("\n");
	
	free_dllist(queue);
}

int main(){
	Graph g = createGraph();
	int nVer;
	nVer = readFromFile(g, "input.txt");
	if(DAG(g) == 1){
	    topology(g, nVer, printVertices);
	}else{
		printf("Do thi co chu trinh khong the sap xep topology");
	}
	return 1;
}
