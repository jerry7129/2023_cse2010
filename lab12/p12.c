#include<stdio.h>
#include<stdlib.h>

typedef struct _Queue {
	int size;
	int* key;
	int front;
	int rear;
} Queue;

Queue* CreateQueue(int X) {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->size = X;
	q->key = (int*)malloc(sizeof(int) * X);
	q->front = 0;
	q->rear = -1;
	return q;
}

void Enqueue(Queue* Q, int item) {
	if (Q->rear >= Q->size) {
		printf("Queue is full!\n");
		exit(1);
	}
	Q->key[++Q->rear] = item;
}

int Dequeue(Queue* Q) {
	if (Q->front > Q->rear) {
		printf("Queue is empty!\n");
		exit(1);
	}
	return Q->key[Q->front++];
}

typedef struct _Graph {
	int size;
	int* vertex;
	int** edge;
} Graph;

Graph* CreateGraph(int X) {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->size = X;
	g->vertex = (int*)malloc(sizeof(int) * X);
	g->edge = (int**)malloc(sizeof(int*) * X);
	for (int i = 0; i < X; i++)
		g->edge[i] = (int*)malloc(sizeof(int) * X);
	
	for (int i = 0; i < X; i++)
		for (int j = 0; j < X; j++)
			g->edge[i][j] = 0;

	return g;
}

void InsertEdge(Graph* G, int u, int v) {
	int i;
	for (i = 0; i < G->size; i++) {
		if (G->vertex[i] == u)
			break;
	}
	int j;
	for (j = 0; j < G->size; j++) {
		if (G->vertex[j] == v)
			break;
	}
	G->edge[i][j] = 1;
}

void Topsort(Graph* G) {
	Queue* q = CreateQueue(G->size);
	int* indegree = (int*)malloc(sizeof(int) * G->size);
	int* visit = (int*)malloc(sizeof(int) * G->size);
	for (int j = 0; j < G->size; j++) {
		int ref = 0;
		for (int i = 0; i < G->size; i++) {
			ref += G->edge[i][j];
		}
		indegree[j] = ref;
	}
	for (int i = 0; i < G->size; i++) {
		visit[i] = 0;
	}

	for (int i = 0; i < G->size; i++) {
		if (indegree[i] == 0) {
			Enqueue(q, G->vertex[i]);
			visit[i] = 1;
		}
	}
	if (q->rear < q->front || q->rear == -1) {
		printf("Topological sorting is impossible.\n");
		exit(1);
	}

	while (q->rear >= q->front || q->rear == -1) {
		int a = Dequeue(q);
		printf("%d ", a);
		int i;
		for (i = 0; i < G->size; i++)
			if (G->vertex[i] == a)
				break;
		for (int j = 0; j < G->size; j++) {
			if (G->edge[i][j] == 1)indegree[j]--;
		}

		for (int i = 0; i < G->size; i++) {
			if (indegree[i] == 0 && visit[i] == 0) {
				Enqueue(q, G->vertex[i]);
				visit[i] = 1;
			}
		}
	}
	printf("\n");
}

int main(int argc, char* argv[]) {
	FILE* fi = fopen(argv[1], "r");
	int X, u, v;

	fscanf(fi, "%d", &X);

	Graph* G = CreateGraph(X);

	for (int i = 0; i < X; i++) {
		fscanf(fi, "%d", &G->vertex[i]);
	}

	while (fscanf(fi, "%d %d", &u, &v) != EOF) {
		InsertEdge(G, u, v);
	}

	Topsort(G);

	return 0;
}
