#include<stdio.h>
#include<stdlib.h>

struct MergeSort {
	int Capacity;
	int Size;
	int* array;
	int* Tmparray;
};

typedef struct MergeSort* MergeSort;

MergeSort make_list(int size);
void Insert(MergeSort m, int a);
void printArray(MergeSort A, int l, int r);
void RmergeSort(MergeSort A, int l, int r);
void ImergeSort(MergeSort A, int n);
void merge(MergeSort A, int l, int m, int r);

void main(int argc, char* argv[]) {
	int size, key;
	int* iter_tmp, * rec_tmp;
	FILE* fi = fopen(argv[1], "r");
	MergeSort iter_m, rec_m;

	fscanf(fi, "%d", &size);

	iter_m = make_list(size);
	rec_m = make_list(size);

	for (int i = 0; i < size; i++) {
		fscanf(fi, "%d", &key);
		Insert(iter_m, key);
		Insert(rec_m, key);
	}

	printf("input : \n");
	printArray(iter_m, 0, iter_m->Size - 1);
	printf("\n");

	printf("iterative : \n");
	ImergeSort(iter_m, iter_m->Size - 1);
	printf("\n");

	printf("recursize : \n");
	RmergeSort(rec_m, 0, rec_m->Size - 1);
	printf("\n");
}

MergeSort make_list(int size) {
	MergeSort m = (MergeSort)malloc(sizeof(struct MergeSort));
	m->Capacity = -1;
	m->Size = size;
	m->array = (int*)malloc(sizeof(int) * size);
	m->Tmparray = (int*)malloc(sizeof(int) * size);
	return m;
}

void Insert(MergeSort m, int a) {
	if (m->Capacity >= m->Size - 1) {
		printf("List is full!\n");
		exit(1);
	}
	m->array[++m->Capacity] = a;
}

void printArray(MergeSort A, int l, int r) {
	for (int i = l; i <= r; i++) {
		printf("%d ", A->array[i]);
	}
	printf("\n");
}

void RmergeSort(MergeSort A, int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;
		RmergeSort(A, l, m);
		RmergeSort(A, m + 1, r);
		merge(A, l, m + 1, r);
		printArray(A, l, r);
	}
}

void ImergeSort(MergeSort A, int n) {
	int a = 2;
	while (a <= n) {
		int i = 0;
		for (i = 0; i + a - 1 <=n; i+=a) {
			merge(A, i, i + a / 2, i + a - 1);
			printArray(A, i, i + a - 1);
		}
		if (i <= n) {
			printArray(A, i , n);
		}
		a *= 2;
	}
	merge(A, 0, a / 2, n);
	printArray(A, 0, n);
}

void merge(MergeSort A, int l, int m, int r) {
	int LeftEnd, NumElements, TmpPos;
	LeftEnd = m - 1;
	TmpPos = l;
	NumElements = r - l + 1;

	while (l <= LeftEnd && m <= r) {
		if (A->array[l] <= A->array[m]) {
			A->Tmparray[TmpPos++] = A->array[l++];
		}
		else
			A->Tmparray[TmpPos++] = A->array[m++];
	}
	while (l <= LeftEnd)
		A->Tmparray[TmpPos++] = A->array[l++];
	while (m <= r)
		A->Tmparray[TmpPos++] = A->array[m++];

	for (int i = 0; i < NumElements; i++)
		A->array[r - i] = A->Tmparray[r - i];
}
