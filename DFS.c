#include<stdio.h>
#include<stdlib.h>


//Possible number of vertices as each vertice is identified by its
//ASCII code so that its parent is identified by accessing the parent
//array with index being the ASCII code for that particular character
#define VERTEX_COUNT 256


/*
 * execute as ./executable < input.graph
 * stores the graph as and adjacency list
 */

/*
 * parent array remembers which all nodes have
 * been visited so when we are recursively visiting
 * nodes we can skip those already visited
 */
char parent[VERTEX_COUNT];

typedef struct node {
	char vertex;
	struct node * next;
}NODE;

/*Count keeps a count of the number of vertices */
int count = 0;



void Dfs_Visit(NODE *vertex, NODE *adj[])
{
	int i;
	for(i = 0; i < count; i++) {
		if(adj[i]->vertex == vertex->vertex) 
			break;
	}
	NODE *temp = adj[i]->next;
	while(temp != NULL) {
		if(parent[temp->vertex] == '\0') {
			parent[temp->vertex] = adj[i]->vertex;
			Dfs_Visit(temp, adj);
		}
		temp = temp->next;
	}
}

void DFS(NODE *adj[])
{
	int i;
	for(i = 0; i < count; i++) {
		if(parent[adj[i]->vertex] == '\0') {
			parent[adj[i]->vertex] = '0';
			Dfs_Visit(adj[i], adj);
		}
	}
}

int main(int argc, char *argv[])
{
	char ch;
	NODE * adj[VERTEX_COUNT];
	int i = 0;
	int new_node = 0;

	for (i = 0; i < VERTEX_COUNT; i++)
	       parent[i] = '\0';	

	while((ch = getchar()) != EOF)
	{
		NODE * temp = NULL;
		if(ch == ' ') {
			new_node++;
			continue;
		}
		if(ch == '\n') {
			new_node = 0;
			count++;
			continue;
		}
		
		temp = malloc(sizeof(NODE));
		temp->vertex = ch;
		temp->next = NULL;
	
		if(new_node == 0) {
			adj[count] = temp;  
		} else {
			NODE * link = adj[count];
			while(link->next != NULL) {
				link = link->next;
			}
			link->next = temp;
		}
	}
	
	DFS(adj);

	printf("node\tparent\n");
	for(i = 0; i < count; i++) {
		printf("%c\t%c\n", adj[i]->vertex, parent[adj[i]->vertex]);
	}	

}
