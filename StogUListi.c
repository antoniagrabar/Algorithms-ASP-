#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

typedef struct Node{
    struct Node *next;
    int val;
} node;

int pop(node **top) {
    if(!*top) return -1;

    node *tmp = (*top)->next;
    free(*top);
    *top = tmp;
    return 0;
}

int push(node **top, int val) {

    node *newn;
    newn = malloc(sizeof(node));

    //newn == NULL alokacija nije uspjela
    if (!newn) return -1;

    newn->val = val;
    newn->next = *top;

    *top = newn;

    return 0;
}

int print(node *top) {

    if(!top) return -1;

    printf("Stog: ");
    for (node *t = top; t != NULL; t = t->next){
        printf("%d ", t->val);
    }
    printf("\n");

    return 0;
}

int main() {
    node *top = NULL;
    char menu_choice;
    int val, retval;

    do {
        DEBUG("\n(d) dodaj - push\n(b) brisi - pop\n(i) ispis - print\n(e) Exit\n");

        scanf(" %c", &menu_choice);
        switch (menu_choice) {
            case 'd':
                scanf("%d", &val);
                retval = push(&top, val);
                if (retval==-1) printf("Alokacija nije uspjela.\n");
                break;
            case 'b':
                retval = pop(&top);
                if (retval==-1) printf("Stog je prazan.\n");
                break;
            case 'i':
                retval = print(top);
                if (retval==-1) printf("Stog je prazan.\n");
                break;
        }
    } while(menu_choice!='e');

    return 0;
}
