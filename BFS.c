#include<stdio.h>
#include <stdlib.h>

#include "readgraph.h"
#define INFINITE	999	//infinite distance

int  ENQUEUE(NODE *Queue[], NODE * vertex,int head, int tail)
{	

	int i;
	printf("The Queue enqued\n");
	

	if(tail == head-1 || (head == 0 && tail == VERTEXSIZE)) {
		printf("Queue Full\n");
		return tail;
	}
	Queue[tail] = vertex;
	tail++;
	for(i = head; i<tail; i++) {
		printf("%d\t", Queue[i]->vertex);
	}
	printf("\n");
	
	return tail;
} 


NODE * DEQUEUE(NODE *Queue[], int *headptr, int *tailptr) {

	
	printf("The Queue dequed\n");
	printf("%d\t", Queue[*headptr]->vertex);
	printf("\n");

	if(*headptr == *tailptr) {
		printf("Empty queue\n");
		return NULL;
	}
	else {
		if(*headptr == VERTEXSIZE) {
			*headptr = 0;
			return Queue[VERTEXSIZE];
		}
		else {
			(*headptr)++;	
			return Queue[(*headptr)-1];
		}
		
	}

}

void BFS(NODE * AdjacencyList[], int n)
{
	NODE *Queue[VERTEXSIZE];
	int head = 0;
	int tail = 0;

	int i = 0;
	for(i = 1; i < n;i++) {	
		AdjacencyList[i]->color = 0;
		AdjacencyList[i]->dist = INFINITE;
		AdjacencyList[i]->predecessor = NULL;	

	}
	AdjacencyList[0]->color = 1;	//source colored GRAY
	AdjacencyList[0]->dist = 0;
	AdjacencyList[0]->predecessor = NULL;
	
	tail = ENQUEUE(Queue, AdjacencyList[0], head, tail);	

	while(tail != head) {
		printf("\n");
		NODE * temp = DEQUEUE(Queue, &head, &tail);
		temp = AdjacencyList[temp->vertex];
		NODE * tempPrev = temp;
		temp = temp->next;
		while(temp != NULL) {
			if(AdjacencyList[temp->vertex]->color == 0) {
				AdjacencyList[temp->vertex]->color = 1;
				AdjacencyList[temp->vertex]->dist = AdjacencyList[tempPrev->vertex]->dist + 1;
				AdjacencyList[temp->vertex]->predecessor = AdjacencyList[tempPrev->vertex];
				tail = ENQUEUE(Queue, temp, head, tail);
			}
			temp = temp->next;
		}
		AdjacencyList[tempPrev->vertex]->color = 2;
		printf("\nhead :%d \ttail: %d", head, tail);
	}
	
}


int 
main(int argc, char *argv[])
{

	int i;
	if(argc < 2) {
		printf("Usage ./executable <inputfile>\n");
		exit(-1);
	}	
	NODE * AdjacencyList[VERTEXSIZE];
	int Vertices;
	Vertices = readfile(argv[1], AdjacencyList);

	printf("\n%d Vertices\n", Vertices);

	for(i=0; i<Vertices; i++) {
		NODE *temp = AdjacencyList[i];
		while(temp != NULL) {
			printf("%d\t", temp->vertex);
			temp = temp->next;
		}
		printf("\n");
	}

	BFS(AdjacencyList, Vertices);

	printf("\nBACK TO MAIN\n");
	
	for(i = 0; i < Vertices; i++) {
		printf("Level of vertice %d Is %d\n", i, AdjacencyList[i]->dist );
	}	
	return 0;	
}
