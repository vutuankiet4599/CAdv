#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dllist.h"
#include "fields.h"
#include "weightedGraphlib.h"

#define MAX 2000
Graph g;
double PR[MAX];

int readWebpage(char *filename)
{
	IS is = new_inputstruct(filename);

	int n;
	int id;
	char *name;
	int i;
	get_line(is);

	n = atoi(is->fields[0]);

	for(i = 0; i < n; i++)
	{
		get_line(is);
		name = strdup(is->fields[0]);
		id = atoi(is->fields[1]);
		addVertex(g, id, name);
	}

	jettison_inputstruct(is);
	return n;
}

int readPageCon(char *filename)
{
	IS is = new_inputstruct(filename);
	int n;
	get_line(is);
	n = atoi(is->fields[0]);
	int i, k;
	int id1, id2;

	for(k = 0; k < n; k++)
	{
		get_line(is);
		id1 = atoi(is->fields[0]);
		for(i = 1; i < is->NF; i++)
		{
			id2 = atoi(is->fields[i]);
			addEdge(g, id1, id2, 1.0);
		}
	}

	jettison_inputstruct(is);
	return n;
}

void pageRank()
{
	int n, n1, id, id1;
	int path[MAX], path1[MAX];
	double val;
	JRB node;
	jrb_traverse(node, g->vertices)
	{
		id = jval_i(node->key);
		n = indegree(g, id, path);
		val = 0;
		for(int i = 0; i < n; i++)
		{
			id1 = path[i];
			n1 = outdegree(g, id1, path1);
			val += PR[id1]/n1;
		}
		PR[id] = val;
	}
}

double dijikstra(Graph graph, int start, int stop, int *path, int *length){
	double total, distance[MAX];
	int min, id, i, n, neighbor, position, previous[MAX], output[MAX], temp[MAX];
	Dllist queue, shortest, node;
	
	for(i = 0; i < MAX; i++){
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

int main(int argc, char const *argv[])
{	
	g = createGraph();
	int key;
	int nWeb;
	int nLink;
	int pathin[MAX];
	int pathout[MAX];
	int nin, nout, count1, count2;
	int test[MAX];
	int id_1, id_2;
	JRB node;

	do
	{
		printf("========================\n");
		printf("1: Doc file\n");
		printf("2: Page Rank 1 lan\n");
		printf("3: Page Rank ?? lan\n");
		printf("4: In ra so luong web chi co lien ket den va so luong spam bot\n");
		printf("5: Duong di ngan nhat\n");
		printf("6: Thoat\n");
		printf("========================\n");
		scanf("%d",&key);

		switch(key)
		{
			case 1:
				nWeb = readWebpage("webpages.txt");
				nLink = readPageCon("pageConnections.txt");

				printf("So luong webpages: %d\n", nWeb);

				jrb_traverse(node, g->vertices)
				{
					printf("%d %s\n", jval_i(node->key), getVertex(g, jval_i(node->key)));
				}
				int inMax, inMin, idMax, idMin, n;
				inMin = MAX;
				inMax = -1;
				int path[MAX];
				jrb_traverse(node, g->vertices)
				{
					n = indegree(g, jval_i(node->key), path);
					if(inMin > n)
					{
						inMin = n;
						idMin = jval_i(node->key);
					}
					if(inMax < n)
					{
						inMax = n;
						idMax = jval_i(node->key);
					}
				}

				printf("Webpage co nhieu lien ket toi nhat:\n");
				printf("%s\n", getVertex(g, idMax));
				printf("Webpage co it lien ket toi nhat:\n");
				printf("%s\n", getVertex(g, idMin));
				break;

			case 2:
				for(int i = 0; i < MAX; i++)
				{
					PR[i] = 1;
				}
				pageRank();
				jrb_traverse(node, g->vertices)
				{
					printf("%d %f\n", jval_i(node->key), PR[jval_i(node->key)]);
				}

				double prMax, prMin;
				int idmAx, idmIn;
				prMax = 0;
				prMin = MAX;
				jrb_traverse(node, g->vertices)
				{
					if(prMax < PR[jval_i(node->key)])
					{
						prMax = PR[jval_i(node->key)];
						idmAx = jval_i(node->key);
					}
					if(prMin > PR[jval_i(node->key)])
					{
						prMin = PR[jval_i(node->key)];
						idmIn = jval_i(node->key);
					}
				}

				printf("Web co trong so PR cao nhat:\n");
				printf("%s\n", getVertex(g, idmAx));
				printf("Web co trong so PR thap nhat:\n");
				printf("%s\n", getVertex(g, idmIn));
				break;

			case 3:
				for(int i = 0; i < MAX; i++)
				{
					PR[i] = 1;
				}

				printf("Nhap so lan lap page rank:\n");
				int m;
				scanf("%d",&m);
				while(m < 10 || m > 50)
				{
					printf("So nhap khong hop le. Moi nhap lai!\n");
					scanf("%d", &m);
				}
				for(int i = 0; i < m; i++)
				{
					pageRank();
				}

				double max;
				int idmax;

				printf("Top 3 web quan trong nhat:\n");

				for(int i = 0; i < 3; i++)
				{
					max = 0;
					jrb_traverse(node, g->vertices)
					{
						if(PR[jval_i(node->key)] > max)
						{
							max = PR[jval_i(node->key)];
							idmax = jval_i(node->key);
						}
					}
					PR[idmax] = 0;
					printf("%s\n", getVertex(g, idmax));
				}
				break;

			case 4:
				count1 = 0;
				count2 = 0;
				jrb_traverse(node, g->vertices)
				{
					nin = indegree(g, jval_i(node->key), test);
					nout = indegree(g, jval_i(node->key), test);
					if(nin == 0 && nout != 0)
					{
						count2 ++;
					}

					if(nin != 0 && nout ==0)
					{
						count1 ++;
					}
				}

				printf("So luong web chi co lien ket den: %d\n", count1);
				printf("So luong spam bot: %d\n", count2);
				break;
			case 5:
				printf("Nhap id1:\n");
				scanf("%d", &id_1);
				printf("Nhap id2:\n");
				scanf("%d", &id_2);
				int dem = 0;

				printf("Duong di ngan nhat:\n");

				if(id_1 == id_2)
				{
					printf("-1");
					break;
				}

				jrb_traverse(node, g->vertices)
				{
					if(jval_i(node->key) == id_1 || jval_i(node->key) == id_2)
					{
						dem ++;
					}
				}
				if(dem < 2)
				{
					printf("-1");
					break;
				}
				double total;
				int length;
				total = dijikstra(g, id_1, id_2, test, &length);
				if(total == INFINITIVE_VALUE)
				{
					printf("-1");
				}else
				{
					printf("%d\n", (int)total);
				}
				break;
			default :
				break;
		}
	}while(key != 6);
	return 0;
}