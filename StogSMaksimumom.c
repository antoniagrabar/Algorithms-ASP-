#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAXS 1000001

typedef struct {
  int top;
  int *arr;
} stack;

stack *stack_ctor(int size) {
  stack *s = malloc(sizeof(stack));
  s->top = -1;
  s->arr = malloc(size*sizeof(int));
  return s;
}

void stack_dtor(stack *s) {
  free(s->arr);
  free(s);
}

int stack_is_empty(stack *s) {
  return s->top==-1;
}

void stack_push(stack *s, int val) {
  s->arr[++(s->top)] = val;
}

void stack_pop(stack *s) {
  if (stack_is_empty(s)) return;
  s->top--;
}

void stack_clear(stack *s) {
  s->top = -1;
}

void maksimum(stack *s, stack *tmp){

  if (stack_is_empty(s)){
    printf("-\n");
  } else {
    printf("%d\n", tmp->arr[tmp->top] );
  }
  
}


int main() {
  int n, max = 0;
  char *op = malloc(6*sizeof(char));
  stack *s = stack_ctor(MAXS); //pocetni stack
  stack *tmp = stack_ctor(MAXS); //stack maksimuma
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf(" %s", op);
    if (strcmp(op, "push")==0) {
      int x;
      scanf(" %d", &x);
      if(stack_is_empty(s) || x >= tmp->arr[tmp->top]) stack_push(tmp, x);
      stack_push(s, x);
    } else if (strcmp(op, "pop")==0) {
      if(!stack_is_empty(s) && s->arr[s->top] == tmp->arr[tmp->top]) stack_pop(tmp);
      //ako nisu jednaki brišemo samo iz s stacka jer je broj toliko mali da nije završio u tmp
      stack_pop(s);
    } else if (strcmp(op, "max")==0) {
      maksimum(s, tmp);
    }
  }
  stack_dtor(s);
  free(op);
  return 0;
}
