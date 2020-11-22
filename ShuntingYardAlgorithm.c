#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAXN 1000000

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
  if(stack_is_empty(s)) return;
  s->top--;
}

char stack_top(stack *s){
  if(stack_is_empty(s)) return (char)-1;
  return s->arr[s->top];
}

int is_operator(char e) {
  if (e=='+' || e=='-' || e=='*' || e=='/' || e=='%') return 1;
  return 0;
}

int priority(char e) {
  if (e=='*' || e=='/' || e=='%') return 2;
  if (e=='+' || e=='-') return 1;
  return 0;
}

void infix2postfix(char *infix, char *postfix){
  stack *operator_stack = stack_ctor(MAXN);

  while(*infix){
    if(*infix == ' '){
      //preskoci
    } else if (isalpha((int)*infix)){ //ako je operand prebaci ga direktno u postfix
      *postfix++ = *infix;
    } else if(*infix == '('){ //otvorene zagrade prebaci na operator_stack
      stack_push(operator_stack, *infix);
    } else if (*infix == ')') {  // na pojavu zatvorene zagrade
      do {
        *postfix++ = stack_top(operator_stack);  // prebacuj operatore sa stoga u p
        stack_pop(operator_stack);
      } while (stack_top(operator_stack)!='(');  // sve do nailaska odgovarajuce otvorene zagrade
      stack_pop(operator_stack);
    }  else if(is_operator(*infix)){
      // sve dok na stacku postoje operatori kojima je prioritet >= prioriteta operatora *infix
        while(!stack_is_empty(operator_stack) && priority(stack_top(operator_stack)) >= priority(*infix)){
          *postfix++ = stack_top(operator_stack); //premjesti ih u postfix
          stack_pop(operator_stack);
        }
        stack_push(operator_stack, *infix); //naposlijetku prebaci operator *infix u operator_stack
    }

    ++infix;
  }

  while (!stack_is_empty(operator_stack)) {
    *postfix++ = stack_top(operator_stack);  // prebaci preostale operatore u postfix
    stack_pop(operator_stack);
  }

  *postfix = '\0';
  stack_dtor(operator_stack); 
}


typedef struct node{
  char value;
  struct node *left, *right;
} Node;


Node *create_binary_tree(char *post){
  Node *n;
  Node **stack = malloc(MAXN*sizeof(Node*));
  int top = -1;

  while(*post){
    n = malloc(sizeof(Node));
    n->value = *post;
    n->left = NULL;
    n->right = NULL;

    if (is_operator(*post)){
      n->right = stack[top--];
      n->left = stack[top--];
    }

    stack[++top] = n;
    post++;
  }

  n = stack[top--];
  free(stack);
  return n;
}

void print_pre_order(Node *n){
  if (n == NULL) return;

  printf("%c", n->value);
  print_pre_order(n->left);
  print_pre_order(n->right);
}

void print_in_order(Node *n) {
  if (n==NULL) return;

  print_in_order(n->left);
  printf("%c", n->value);
  print_in_order(n->right);
}

void print_post_order(Node *n) {
  if (n==NULL) return;

  print_post_order(n->left);
  print_post_order(n->right);
  printf("%c", n->value);
}



int main() {

  int n;
  char *infix, *postfix;
  Node *root = NULL;

  scanf("%d", &n);
  infix = malloc((n+1)*sizeof(char));
  postfix = malloc((n+1)*sizeof(char));

  scanf(" %1000000[^\r\n]", infix);

  infix2postfix(infix, postfix);
  printf("Postfix: %s\n", postfix);

  root = create_binary_tree(postfix);
  printf("Pre-order: ");
  print_pre_order(root);
  printf("\nIn-order: ");
  print_in_order(root);
  printf("\nPost-order: ");
  print_post_order(root);
  printf("\n");

  free(infix);
  free(postfix);
  
  return 0;
}
