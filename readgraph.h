#include<stdio.h>

#define VERTEXSIZE 100


typedef struct node {
	int vertex;
	int dist;
	struct node * next;
	struct node *predecessor; //predecessor in BFS 
	int color;		//0 WHITE, 1:Gray , 2: Black
}NODE;


int readfile(char *, NODE **);
