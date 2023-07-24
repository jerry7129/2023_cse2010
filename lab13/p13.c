#include<stdio.h>
#include<stdlib.h>

const int INF = (int)2e9;

typedef struct Node {
	int vertex;
	int dist;
	int prev;
}Node;

typedef struct Graph {
	int size;
	Node* nodes;
	int** matrix;
}Graph;

Graph* createGraph(int X);
Graph* findShortestPath(Graph* G, int s);
void printShortestPath(Graph* G);

typedef struct Heap {
	int capacity;
	int size;
	Node* elements;
}Heap;

Heap* createMinHeap(int X);
void insert(Heap* H, Node N);
Node deleteMin(Heap* H);
void decreaseKey(Heap* H, Node N);

int main(int argc, char* argv[]) {
	FILE* fi = fopen(argv[1], "r");
	int size;

	fscanf(fi, "%d", &size);

	Graph* G = createGraph(size);

	int node_s, node_d, weight;
	while (fscanf(fi, "%d %d %d", &node_s, &node_d, &weight) != EOF) {
		G->matrix[node_s][node_d] = weight;
	}

	G = findShortestPath(G, 1);

	printShortestPath(G);
}

Heap* createdMinHeap(int X) {
	Heap* h = (Heap*)malloc(sizeof(Heap));
	h->capacity = X;
	h->size = 0;
	h->elements = (Node*)malloc(sizeof(Node) * X);
	return h;
}
void insert(Heap* H, Node N) {
	int i;
	if (H->capacity <= H->size) {
		printf("Min Heap is full.\n");
		exit(1);
	}
	for (i = ++H->size; H->elements[i / 2].dist > N.dist; i /= 2)
		H->elements[i] = H->elements[i / 2];
	H->elements[i] = N;
}
Node deleteMin(Heap* H) {
	int i, Child;
	Node Min, Last;

	Min = H->elements[1];
	Last = H->elements[H->size--];

	for (i = 1; i * 2 <= H->size; i = Child) {
		Child = i * 2;
		if (Child != H->size && H->elements[Child + 1].dist < H->elements[Child].dist)
			Child++;

		if (Last.dist > H->elements[Child].dist)
			H->elements[i] = H->elements[Child];
		else break;
	}

	H->elements[i] = Last;
	return Min;
}
void decreaseKey(Heap* H, Node N) {
	int i;
	for (i = H->size; i >= 1; i--) {
		if (H->elements[i].vertex == N.vertex)
			break;
	}
	while(N.dist < H->elements[i/2].dist) {
		H->elements[i] = H->elements[i / 2];
		i /= 2;
	}
	H->elements[i] = N;
}

Graph* createGraph(int X) {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->size = X + 1;

	g->nodes = (Node*)malloc(sizeof(Node) * (X + 1));
	for (int i = 0; i < X + 1; i++) {
		g->nodes[i].vertex = i;
		g->nodes[i].dist = INF;
		g->nodes[i].prev = i;
	}

	g->matrix = (int**)malloc(sizeof(int*) * (X + 1));
	for (int i = 0; i < X + 1; i++)
		g->matrix[i] = (int*)malloc(sizeof(int) * (X + 1));
	for (int i = 0; i < g->size; i++)
		for (int j = 0; j < g->size; j++)
			g->matrix[i][j] = 0;

	return g;
}
Graph* findShortestPath(Graph* G, int s) {
	Heap* H = createdMinHeap(G->size - 1);
	for (int i = 2; i < G->size; i++) {
		if (G->matrix[1][i] != 0) {
			G->nodes[i].dist = G->matrix[1][i];
			G->nodes[i].prev = 1;
		}
	}
	for (int i = 2; i < G->size; i++)
		insert(H, G->nodes[i]);

	while (H->size > 0) {
		Node target = deleteMin(H);
		for (int i = 2; i < G->size; i++) {
			if (G->matrix[target.vertex][i] != 0)
				if (target.dist + G->matrix[target.vertex][i] < G->nodes[i].dist) {
					G->nodes[i].dist = target.dist + G->matrix[target.vertex][i];
					G->nodes[i].prev = target.vertex;
					decreaseKey(H, G->nodes[i]);
				}
		}
	}
	return G;
}
void printShortestPath(Graph* G) {
	for (int i = 2; i < G->size; i++) {
		int j = i;
		while (G->nodes[j].vertex != G->nodes[j].prev) {
			printf("%d<-", G->nodes[j].vertex);
			j = G->nodes[j].prev;
		}
		if (G->nodes[j].vertex == 1)
			printf("%d cost: %d\n", G->nodes[j].vertex, G->nodes[i].dist);
		else
			printf("%d can not be reached.\n", i);
	}
}
