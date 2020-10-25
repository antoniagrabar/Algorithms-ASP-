#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif



	typedef struct {
		int *arr;
		int top;
	} stack;

	stack *stack_ctor(int size){
		stack *s = malloc(sizeof(stack));
		s->arr = malloc(size * sizeof(int));
		s->top = -1;
		return s;
	}

	void stack_dtor(stack *s){
		free(s->arr);
		free(s);
	}

	int stack_is_empty(stack *s){
		return s->top == -1;
	}

	void stack_push(stack *s, int val){
		s->arr[++(s->top)] = val;
	}

	void stack_pop(stack *s){
		if (stack_is_empty(s)) return;
		s->top--;
	}

	int stack_top(stack *s){
		if(stack_is_empty(s)) return -1;
		return s->arr[s->top];
	}


int main() {

	int n;
	scanf("%d\n", &n);
	stack *s = stack_ctor(n);

	for (int i = 0; i < n; ++i){
		char c;
		scanf("%c ", &c);

		if ('0'<= c && c <= '9'){
			stack_push(s, c-'0');
		} else {
			int res;
			int b = stack_top(s);
			stack_pop(s);
			int a = stack_top(s);
			stack_pop(s);

			switch(c){
				case '+':
					res = a + b;
					break;
				case '-':
					res = a - b;
					break;
				case '*':
					res = a * b;
					break;
			}

			stack_push(s, res);
		}
	}

	printf("%d", stack_top(s) );
}