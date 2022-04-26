#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	int **matrix;
	int sizemax;
}Graph;

Graph createGraph(int size){
	Graph p;
	p.matrix = (int**)malloc(sizeof(int*)*size);
    p.sizemax = size;
    
	for(int i = 0; i < size; i++)
	{
		p.matrix[i] = (int*)malloc(size*sizeof(int));
	}
	
	for(int i = 0; i < size; i++)
	{
		for(int j = i; j < size; j++)
		{
			p.matrix[i][j] = 0;
			p.matrix[j][i] = 0;
		}
	}
	
	return p;
}

void setEdge(Graph *p, int v1, int v2)
{
	p->matrix[v1][v2] = 1;
	p->matrix[v2][v1] = 1;
}

int connected(Graph p, int v1, int v2)
{
	if( p.matrix[v1][v2] == 1 ) return 1;
	else return 0;
}

int getConnectedVertices(Graph graph, int vertex, int *output)
{
	int count;
	output[vertex] = 1;
	
	for(int i = 0; i < graph.sizemax; i++)
	{
		if(connected(graph, vertex, i) && output[i] == 0)
		{
			getConnectedVertices(graph, i, output);
		}
	}
	
	for(int j = 0; j < graph.sizemax; j++)
	{
		if(output[j] == 1)
		count ++;
	}
	
	return count;
}

void findDirectConnected(Graph graph, int vertex, int *output)
{
	int j = 0;
	for(int i = 0; i < graph.sizemax; i++){
		if(graph.matrix[vertex][i] == 1){
			output[j] = i;
			j++;
		}
	}
}

int numberoftrain()
{
	FILE *fptr;
	fptr = fopen("input.txt","r");
	char p[30];
	char test[30];
	strcpy(test, "LINES");
	int i = 0;
	fgets(p, 30, fptr);
    
	while(1)
	{
		fgets(p, 30, fptr);
		if(!(strcmp(p, test)-10))
		{
			fclose(fptr);
	        return i;
		}
		i++;
	}
	return i;
	
}


int numberofline()
{
	FILE *fptr;
	fptr = fopen("input.txt","r");
	char p[30];
	int i = 0;
	fgets(p, 30, fptr);
	
	while(1)
	{
		fgets(p, 30, fptr);
		if(strcmp(p,"LINES") - 10 == 0) break;
	}
	
	while(!feof(fptr))
	{
		fgets(p, 30, fptr);
		i++;
	}
	i--;
	fclose(fptr);
	return i;
}



Graph readFormFile(char **train, int **line)
{
	FILE *fptr;
	fptr = fopen("input.txt","r");	
	Graph graph;
	
	int j = 0;
	int size = numberoftrain();
	graph = createGraph(size);
	char p[30];
	char number[2];
	char name[30];
	
	fgets(p, 30, fptr);
	
	for(int i = 0; i < size; i++){
		fgets(p, 30, fptr);
		strcpy(name, strstr(p," "));
		strcpy(number ,strtok(p, "="));
		strcpy(train[atoi(number)], name);
	}

	fgets(p, 30, fptr);
	for(int k = 0; k < numberofline(); k++)
	{
		fgets(p, 30, fptr);
		strcpy(name, strstr(p," "));
		strcpy(number ,strtok(p, "="));
        j = 0;
		for(int i = 0; i < strlen(name); i++)
		{
			if(isdigit(name[i]))
			{
				line[atoi(number)][j] = atoi(name+i)+1;
				j++;
			}
		}
		
	}
	
	for(int i = 0; i < numberofline(); i++)
	{
		for(int k = 0; k < numberoftrain() - 1; k++)
		if(line[i][k] != 0 && line[i][k+1] != 0)
		setEdge(&graph, line[i][k] - 1, line[i][k+1] - 1);
	}
	
	fclose(fptr);
	return graph;
}



int main()
{
	
	Graph graph;
	int ntrain, nline;
	ntrain = numberoftrain();
	nline = numberofline();
	
	char **station;
	int **line;
	
	station = (char**)malloc(sizeof(char*)*ntrain);
	
	for(int i = 0; i < ntrain; i++)
    {
		station[i] = (char*)malloc(sizeof(char)*30);
	}
	
    line = (int**)malloc(sizeof(int*)*nline);
    
    for(int i = 0; i < nline; i++)
    {
		line[i] = (int*)malloc(sizeof(int)*ntrain);
	}
	
	for(int i = 0; i < nline; i++)
	{
		for(int j = 0; j < ntrain; j++)
		line[i][j] = 0;
	}
	
	graph = readFormFile(station, line);
	
	for(int i = 0; i < ntrain; i++)
	{
		for(int j = i; j < ntrain; j++)
		if(graph.matrix[i][j] == 1)printf("%d - %d ",i, j);
	}
	
	
	for(int i = 0; i < ntrain; i++)free(station[i]);
	free(station);
	
	for(int i = 0; i < nline; i++)free(line[i]);
	free(line);
	
	for(int i = 0; i < ntrain; i++)free(graph.matrix[i]);
	free(graph.matrix);
	
	
	return 1;
}
