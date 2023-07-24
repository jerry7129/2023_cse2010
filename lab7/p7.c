#include<stdio.h>
#include<stdlib.h>

struct AVLMode;
typedef struct AVLNode* Position;
typedef struct AVLNode* AVLTree;
typedef int ElementType;

struct AVLNode {
	ElementType Element;
	AVLTree Left;
	AVLTree Right;
	int Height;
};

int Max(ElementType num1, ElementType num2);
int Height(Position P);
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);
AVLTree Insert(ElementType X, AVLTree T);
void PrintInorder(AVLTree T);
void DeleteTree(AVLTree T);

int main(int argc, char** argv) {
	AVLTree myTree = NULL;
	int key;

	FILE* fi = fopen(argv[1], "r");
	while (fscanf(fi, "%d", &key) != EOF) {
		myTree = Insert(key, myTree);
		PrintInorder(myTree);
		printf("\n");
	}
	fclose(fi);

	DeleteTree(myTree);
	return 0;
}

void DeleteTree(AVLTree T) {
	if (T->Left != NULL)
		DeleteTree(T->Left);
	if (T->Right != NULL)
		DeleteTree(T->Right);
	free(T);
}

int Max(ElementType num1, ElementType num2) {
	return num1 > num2 ? num1 : num2;
}

int Height(Position P) {
	if (P == NULL)
		return -1;
	return P->Height;
}

Position SingleRotateWithLeft(Position node) {
	Position K1 = node->Left;
	node->Left = K1->Right;
	K1->Right = node;

	node->Height = Max(Height(node->Left), Height(node->Right)) + 1;
	K1->Height = Max(Height(K1->Left), node->Height) + 1;

	return K1;
}

Position SingleRotateWithRight(Position node) {
	Position K1 = node->Right;
	node->Right = K1->Left;
	K1->Left = node;

	node->Height = Max(Height(node->Left), Height(node->Right)) + 1;
	K1->Height = Max(Height(K1->Right), node->Height) + 1;

	return K1;
}

Position DoubleRotateWithLeft(Position node) {
	node->Left = SingleRotateWithRight(node->Left);
	return SingleRotateWithLeft(node);
}

Position DoubleRotateWithRight(Position node) {
	node->Right = SingleRotateWithLeft(node->Right);
	return SingleRotateWithRight(node);
}

AVLTree Insert(ElementType X, AVLTree T) {
	if (T == NULL) {
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		if (T == NULL) {
			printf("Out of space!!!\n");
			exit(1);
		}
		else {
			T->Element = X;
			T->Left = T->Right = NULL;
		}
	}
	else if (X == T->Element){
		printf("Insertion Error: 23 already in the tree!\n");
		return T;
	}
	else if (X < T->Element) {
		T->Left = Insert(X, T->Left);
		if (Height(T->Left) - Height(T->Right) == 2) {
			if (X < T->Left->Element)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
		}
	}
	else if (X > T->Element) {
		T->Right = Insert(X, T->Right);
		if (Height(T->Right) - Height(T->Left) == 2) {
			if (X > T->Right->Element)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
		}
	}
	T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
	return T;

	return T;
}

void PrintInorder(AVLTree T) {
	if (T == NULL)return;
	PrintInorder(T->Left);
	printf("%d(%d) ", T->Element, T->Height);
	PrintInorder(T->Right);
}
