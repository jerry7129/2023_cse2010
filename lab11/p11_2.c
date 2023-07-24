#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct QuickSort {
	int Capacity;
	int Size;
	int* array;
};

typedef struct QuickSort* QuickSort;

QuickSort make_list(int size);
void Insert(QuickSort q, int a);
void printArray(QuickSort q);
void swap(int* a, int* b);
int middle_partition(QuickSort q, int low, int high);
int leftmost_partition(QuickSort q, int left, int right);
int rightmost_partition(QuickSort q, int left, int right);
void quicksort(QuickSort q, int left, int right, int type);

int main(int argc, char* argv[]) {
	char type_s[10];
	int list_size, key, type_i;
	QuickSort q;
	FILE* fi = fopen(argv[1], "r");

	fscanf(fi, "%s", type_s);
	if (!(strcmp(type_s, "leftmost")))type_i = 0;
	else if (!(strcmp(type_s, "rightmost")))type_i = 1;
	else if (!(strcmp(type_s, "middle")))type_i = 2;

	fscanf(fi, "%d", &list_size);
	q = make_list(list_size);
	for (int i = 0; i < list_size; i++) {
		fscanf(fi, "%d", &key);
		Insert(q, key);
	}
	
	quicksort(q, 0, list_size - 1, type_i);

	free(q->array);
	free(q);
}

QuickSort make_list(int size) {
	QuickSort q = (QuickSort)malloc(sizeof(struct QuickSort));
	q->Capacity = -1;
	q->Size = size;
	q->array = (int*)malloc(sizeof(int) * size);
	return q;
}

void Insert(QuickSort q, int a) {
	q->array[++q->Capacity] = a;
}

void printArray(QuickSort q) {
	for (int i = 0; i < q->Size; i++) {
		printf("%d ", q->array[i]);
	}
	printf("\n");
}

void swap(int* a, int* b) {
	int ref = *a;
	*a = *b;
	*b = ref;
}

int leftmost_partition(QuickSort q, int left, int right) {
	int pivot = q->array[left];
	int i = left;
	int j = right + 1;
	printf("pivot value : %d\n", pivot);
	while (1) {
		while (q->array[--j] > pivot);
		while (q->array[++i] < pivot);
		if (i < j)swap(&q->array[i], &q->array[j]);
		else {
			swap(&q->array[j], &q->array[left]);
			return j;
		}
	}
}

int rightmost_partition(QuickSort q, int left, int right) {
	int pivot = q->array[right];
	int i = left - 1;
	int j = right;
	printf("pivot value : %d\n", pivot);
	while (1) {
		while (q->array[--j] > pivot);
		while (q->array[++i] < pivot);
		if (i < j)swap(&q->array[i], &q->array[j]);
		else {
			swap(&q->array[i], &q->array[right]);
			return i;
		}
	}
}

int middle_partition(QuickSort q, int low, int high) {
	int pivot = q->array[(low + high) / 2];
	printf("pivot value : %d\n", pivot);
	int i = low - 1;
	int j = high + 1;
	while (1) {
		while (q->array[--j] > pivot);
		while (q->array[++i] < pivot);
		if (i < j)
			swap(&q->array[i--], &q->array[j++]);
		else{
			return i;
		}
	}
}

void quicksort(QuickSort q, int left, int right, int type) {
	int p;
	if (left >= right)return;
	if (type == 0)
		p = leftmost_partition(q, left, right);
	else if (type == 1)
		p = rightmost_partition(q, left, right);
	else if (type == 2)
		p = middle_partition(q, left, right);
	printf("result : ");
	printArray(q);
	
	quicksort(q, left, p - 1, type);
	quicksort(q, p + 1, right, type);
}
