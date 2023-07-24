#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct _DisjoingSet {
	int size;
	int* ptr_arr;
}DisjointSets;
typedef struct _PrintDisjointSet {
	int size;
	int* ptr_arr;
}PrintDisjointSets;

void init(DisjointSets* sets, PrintDisjointSets* maze, int n);
int find(DisjointSets* sets, int x);
void union_(DisjointSets* sets, int i, int j);
void createMaze(DisjointSets* sets, PrintDisjointSets* maze, int n);
void printMaze(PrintDisjointSets* maze, int n);
void freeMaze(DisjointSets* sets, PrintDisjointSets* maze);

int main(int argc, char* argv[]) {
	int num;
	FILE* fi = fopen(argv[1], "r");
	fscanf(fi, "%d", &num);
	fclose(fi);

	DisjointSets* sets;
	PrintDisjointSets* maze;

	sets = (DisjointSets*)malloc(sizeof(DisjointSets));
	maze = (PrintDisjointSets*)malloc(sizeof(PrintDisjointSets));

	init(sets, maze, num);
	createMaze(sets, maze, num);
	printMaze(maze, num);
	freeMaze(sets, maze);
	return 0;
}

void init(DisjointSets* sets, PrintDisjointSets* maze, int n) {
	sets->size = n * n + 1;
	sets->ptr_arr = (int*)malloc(sizeof(int) * (n * n + 1));
	for (int i = 0; i < n * n + 1; i++)
		sets->ptr_arr[i] = 0;

	maze->size = 2 * n * n + 2 * n;
	maze->ptr_arr = (int*)malloc(sizeof(int) * (2 * n * n + 2 * n));
	for (int i = 0; i < (2 * n * n + 2 * n); i++)
		maze->ptr_arr[i] = 1;
}

int find(DisjointSets* sets, int x) {
	if (sets->ptr_arr[x] <= 0)
		return x;
	else
		return (sets->ptr_arr[x] = find(sets, sets->ptr_arr[x]));
}

void union_(DisjointSets* sets, int i, int j) {
	int pi = find(sets, i);
	int pj = find(sets, j);
	if (sets->ptr_arr[pj] < sets->ptr_arr[pi])
		sets->ptr_arr[pi] = pj;
	else {
		if (sets->ptr_arr[pi] == sets->ptr_arr[pj])
			sets->ptr_arr[pi]--;
		sets->ptr_arr[pj] = pi;
	}
}

void createMaze(DisjointSets* sets, PrintDisjointSets* maze, int n) {
	while (find(sets, 1) != find(sets, n * n)) {
		srand(time(NULL));
		int random = rand() % (2 * n * n + 2 * n);
		int a, b;
		if (random < n || random >= 2 * n * n + n || random % (2 * n + 1) == n || random % (2 * n + 1) == 2 * n)continue;
		if (random % (2 * n + 1) < n) {
			a = (random / (2 * n + 1) - 1) * n + random % (2 * n + 1) + 1;
			b = a + n;
		}
		else {
			a = random / (2 * n + 1) * n + random % (2 * n + 1) - n;
			b = a + 1;
		}
		if (find(sets, a) != find(sets, b)) {
			union_(sets, a, b);
			maze->ptr_arr[random] = 0;
		}
	}
}

void printMaze(PrintDisjointSets* maze, int n) {
	maze->ptr_arr[n] = 0;
	maze->ptr_arr[2 * n * n + n - 1] = 0;
	for (int i = 0; i < (2 * n * n + 2 * n); i++) {
		if (i % (2 * n + 1) < n) {
			if (maze->ptr_arr[i] == 1)printf(" -");
			else printf("  ");
			if (i % (2 * n + 1) == n - 1)printf("\n");
		}
		else {
			if (maze->ptr_arr[i] == 1)printf("| ");
			else printf("  ");
			if (i % (2 * n + 1) == 2 * n)printf("\n");
		}
	}
}

void freeMaze(DisjointSets* sets, PrintDisjointSets* maze) {
	free(sets->ptr_arr);
	free(sets);
	free(maze->ptr_arr);
	free(maze);
}
