#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

typedef struct Node {
    struct Node *next;
    int val;
} node;

int push(node **top, int val) {
    node *new;
    new = (node *)malloc(sizeof(node));
    if (!new) return -1;

    new->val = val;
    new->next = *top;
    *top = new;

    return 0;
}

int pop(node **top) {
    node *t;

    if(!*top) return -1;

    DEBUG("pop: %d", (*top)->val);

    t = (*top)->next;
    free(*top);
    *top = t;

    return 0;
}

int print(node *top) {
    node *t;

    if(!top) return -1;

    for(t=top; t!=NULL; t=t->next) printf("%d ", t->val);

    return 0;

}

void isprazni(node **top){
    while(*top){
        pop(top);
    }
}

int main() {
    node *top = NULL;
    int menu_choice, val, ret_val;

    do {
        menu_choice = 0;
        //DEBUG("\n1 opis funkcije (ime_funkcije)");
        DEBUG("\n2 dodaj (push)\n3 brisi (pop)\n4 ispis (print)\n5 izlaz\n");
        scanf("%d", &menu_choice);
        switch (menu_choice) {
            case 1:
                isprazni(&top);
                break;
            case 2:
                scanf("%d", &val);
                ret_val = push(&top, val);
                if(ret_val==-1) DEBUG("Alokacija nije uspjela.");
                break;
            case 3:
                ret_val = pop(&top);
                if(ret_val==-1) DEBUG("Stog je prazan.");
                break;
            case 4:
                ret_val = print(top);
                if(ret_val==-1) DEBUG("Stog je prazan.");
                break;
            case 5:
                break;
        }
    } while(menu_choice!=5);


    return 0;
}
