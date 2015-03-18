#include<stdio.h>
#include<stdlib.h>
#include "readgraph.h"


#define BUFSIZE 64

NODE *allocVertex()
{
	return malloc(sizeof(NODE));
}

int readfile(char *filename, NODE *AdjacencyList[])
{
	FILE *fp = NULL;
	int i = 0;
	int count = 0;	
	int ch;
	int index;
		
	NODE  *node = NULL;	
	
	fp = fopen(filename,"r");
	i=0;
	while((ch = fgetc(fp)) != EOF) {
		if(ch == ' ') {
			count++;
			continue;
		}
		if(ch == '\n') {
			count = 0;
			i++;	
			continue;
		}
		if(count == 0) {
			node = allocVertex();
			node->vertex = ch - '0';
			index = node->vertex;
			node->next = NULL;
			node->predecessor = NULL;
			node->color = 0;
			node->dist = 0;
			AdjacencyList[index] = node;
		} else {
			node = allocVertex();
			node->vertex = ch - '0';
			node->color = 0;
			node->dist = 0;
			node->predecessor = NULL;
			node->next = AdjacencyList[index]->next;
			AdjacencyList[index]->next = node;
//			printf("%c\t", AdjacencyList[i]->vertex);
		}
		
	}	
	return i;
}
