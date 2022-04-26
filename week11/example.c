#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "weightedGraphlib.h"
#include "fields.h"
#include "dllist.h"


void readFromFile(char *filename, Graph graph, int **line, int *nbus, int *nline){
	IS is;
	is = new_inputstruct(filename);
	get_line(is);
	*nbus = atoi(is->fields[0]);
	*nline = atoi(is->fields[1]);
	int m = 0;
	int n = 0;

	for(int i = 0; i < *nbus; i++){
		get_line(is);
		int id = atoi(is->fields[0]);
		char *name = strdup(is->fields[1]);
		addVertex(graph, id, name);
	}

	while(get_line(is) > 0){
		n = 0;
		for(int i = 2; i < is->NF; i += 2){
			int v1 = atoi(is->fields[i-2]);
			int v2 = atoi(is->fields[i]);
			double weigth = atof(is->fields[i-1]);
			addEdge(graph, v1, v2, weigth);
			
			line[m][n++] = v1;
			if(i == is->NF -1){
				line[m][n] = v2;
			}
			
		}
		m++;
	}

	jettison_inputstruct(is);


}

int main(int argc, char const *argv[])
{
	Graph g = createGraph();
	int **line;
	int nbus;
	int nline;
	int k;

	line = (int **)malloc(sizeof(int*)*100);
	for(int i = 0; i < 100; i++){
		line[i] = (int*)malloc(sizeof(int)*100);
	}

	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 100; j++){
			line[i][j] = 0;
		}
	}

	readFromFile("input.txt", g, line, &nbus, &nline);

	int length;
	int path[100];
	double total;
	total = dijikstra(g, 1, 5, path, &length);


	printf("Shortest way from Station_A to Station_E is:\n");

	for(int i = 0; i < length; i++){
		printf("%s ",getVertex(g,path[i]));
	}

	printf("\nTotal is: %lf\n", total);

	printf("Lines of bus:\n");

	for(int i = 0; i < nline; i++){
		k = 0;
		while(line[i][k] != 0){
			printf("%s ", getVertex(g, line[i][k]));
			k++;
		}
		printf("\n");
	}
	for(int i = 0; i < 100; i++){
		free(line[i]);
	}
	free(line);
	return 0;
}