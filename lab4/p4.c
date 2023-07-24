#include<stdio.h>
#include<stdlib.h>

typedef struct Stack {
	int* key;
	int top;
	int max_stack_size;
}Stack;

Stack* CreateStack(int max);
void Push(Stack* s, int X);
int Pop(Stack* s);
int Top(Stack* s);
void DeleteStack(Stack* s);
int IsEmpty(Stack* s);
int IsFull(Stack* s);
void Postfix(Stack* s, char intput_str);

void main(int argc, char* argv[]) {
	FILE* fi = fopen(argv[1], "r");
	Stack* stack = CreateStack(10);

	char c;
	int cnt = 0;
	printf("Top numbers: ");
	while (1) {
		fscanf(fi, "%c", &c);
		if (c == '#') break;
		
		++cnt;
		Postfix(stack, c);
		printf("%d ", Top(stack));
		if(cnt > 100){
			printf("Error: Too many expression\n");
			exit(1);
		}
	}
	printf("\n");
	printf("evaluation result: %d\n", Pop(stack));

	fclose(fi);
	DeleteStack(stack);
}

Stack* CreateStack(int max) {
	Stack* s = (Stack*)malloc(sizeof(Stack));
	s->max_stack_size = max;
	s->key = (int*)malloc(sizeof(int) * max);
	s->top = -1;
	return s;
}
void Push(Stack* s, int X) {
	if (IsFull(s)) {
		printf("\nError: Full stack.\n");
		exit(1);
	}
	s->key[++s->top] = X;
}
int Pop(Stack* s) {
	if (IsEmpty(s)) {
		printf("\nError: Empty stack.\n");
		exit(1);
	}
	return s->key[s->top--];
}
int Top(Stack* s){
	return s->key[s->top];
}
void DeleteStack(Stack* s) {
	free(s->key);
	free(s);
}
int IsFull(Stack* s) {
	if (s->top == s->max_stack_size - 1) return 1;
	else return 0;
}
int IsEmpty(Stack* s) {
	if (s->top == -1)return 1;
	else return 0;
}
void Postfix(Stack* s, char input_str) {
	if (input_str >= '0' && input_str <= '9') {
		Push(s, input_str - '0');
	}
	else {
		int a = Pop(s), b = Pop(s);
		switch (input_str) {
		case '+':
			Push(s, b + a);
			break;
		case '-':
			Push(s, b - a);
			break;
		case '*':
			Push(s, b * a);
			break;
		case '/':
			Push(s, b / a);
			break;
		case '%':
			Push(s, b % a);
			break;
		}
	}
}

