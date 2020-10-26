#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

typedef struct Node {
    struct Node *next;
    int val;
} node;

int push(node **top, int val, int *top_top, int *current_top) {
    node *new;
    new = (node *)malloc(sizeof(node));
    if (!new) return -1;

    new->val = val;
    new->next = *top;
    *top = new;

    (*current_top)++;
    if(*current_top > *top_top) *top_top = *current_top;

    return 0;
}

int pop(node **top, int *current_top) {
    node *t;

    if(!*top) return -1;

    DEBUG("pop: %d", (*top)->val);

    t = (*top)->next;
    free(*top);
    *top = t;

    (*current_top)--;

    return 0;
}

int print(node *top) {
    node *t;

    if(!top) return -1;

    for(t=top; t!=NULL; t=t->next) printf("%d ", t->val);

    return 0;

}

void top_topova(int top_top){
    printf("%d\n", top_top);
}

int main() {
    node *top = NULL;
    int menu_choice, val, ret_val, top_top = 0, current_top = 0;
    char c;

    setbuf(stdout, NULL);
    do {
        menu_choice = 0;
        //DEBUG("\n1 opis funkcije (ime_funkcije)");
        DEBUG("\n2 dodaj (push)\n3 brisi (pop)\n4 ispis (print)\n5 izlaz\n");
        scanf("%d", &menu_choice);
        switch (menu_choice) {
            case 1:
                top_topova(top_top);
                break;
            case 2:
                scanf("%d", &val);
                ret_val = push(&top, val, &top_top, &current_top);
                if(ret_val==-1) DEBUG("Alokacija nije uspjela.");
                break;
            case 3:
                ret_val = pop(&top, &current_top);
                if(ret_val==-1) DEBUG("Stog je prazan.");
                break;
            case 4:
                ret_val = print(top);
                if(ret_val==-1) DEBUG("Stog je prazan.");
                break;
            case 5:
                break;
            default:
                while((c = getchar()) != '\n' && c != EOF);
        }
    } while(menu_choice!=5);

    return 0;
}
