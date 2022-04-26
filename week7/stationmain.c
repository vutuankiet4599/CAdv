#include <stdio.h>
#include <string.h>
#include "graphlib.c"
#include "graphlib.h"
#include <ctype.h>
#include <stdlib.h>

//Bai tap so 2 dung JRB bieu dien ga tau dien
int numberofstation()
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

graph readFormFile(char **train, int **line)
{
	FILE *f = fopen("input.txt", "r");
	graph station;

	JRB node;
	char p[30];
	
	station = creategraph();
	
	char name[30];
	char number[2];
	int j = 0;
	
	fgets(p, 30, f);
	for(int i = 0; i < numberofstation(); i++){
		fgets(p, 30, f);
		strcpy(name, strstr(p," "));
		strcpy(number ,strtok(p, "="));
		strcpy(train[atoi(number)], name);
	}
	
	fgets(p, 30, f);
	for(int k = 0; k < numberofline(); k++)
	{
		fgets(p, 30, f);
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
		for(int k = 0; k < numberofstation() - 1; k++)
		if(line[i][k] != 0 && line[i][k+1] != 0)
		addedge(station, line[i][k] - 1, line[i][k+1] - 1);
	}
	
	jrb_traverse(node,station){
    printf("%d ",node->key.i);
    }
    printf("\n");
	fclose(f);
	return station;
}

int main()
{
	graph station;
	char **train;
	int ntrain = numberofstation();
	int nline = numberofline();
	int **line;
	
	train = (char**)malloc(sizeof(char*)*ntrain);
	
	for(int i = 0; i < ntrain; i++)
    {
		train[i] = (char*)malloc(sizeof(char)*30);
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
	station = readFormFile(train, line);
	int num;
	int *output;
	output = (int*)malloc(sizeof(int)*ntrain);

	num = incidentedges(station, 1, output);
	if(num <=0 )printf("NONE\n");
	else printf("%d\n", num);
	
	for(int i = 0; i < ntrain; i++)free(train[i]);
	free(train);
	
	for(int i = 0; i < nline; i++)free(line[i]);
	free(line);
	dropgraph(station);
	return 1;
}
