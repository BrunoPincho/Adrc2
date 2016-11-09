#ifndef PROJ2_H
#define PROJ2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int nodes;
struct node{
	int id;
	int Linktype;
	int seen;
	struct node* next;
};

struct lista{
	int num;
	int len;
	int dist;
	int extension;
	int parent;
	int seen;
	int previous;
	int Pathtype;
	struct node* pointer;
};

struct grafo{
	struct lista* array;
};

struct grafo* criagrafo(int nodes);

void addnode(struct grafo*ref,int tail,int head,int linktype,int Vertices);

void comroute(struct grafo*ref,int destination);

int pathtype(int caminho,int novo);


#endif
