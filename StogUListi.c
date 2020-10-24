#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

typedef struct Node{
    struct Node *next;
    int val;
} node;

int push(/*argumenti*/) {
    return 0;
}

int pop(/*argumenti*/) {
    return 0;
}

int print(/*argumenti*/) {
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
                retval = push(/*argumenti*/);
                if (retval==-1) printf("Alokacija nije uspjela.\n");
                break;
            case 'b':
                retval = pop(/*argumenti*/);
                if (retval==-1) printf("Stog je prazan.\n");
                break;
            case 'i':
                retval = print(/*argumenti*/);
                if (retval==-1) printf("Stog je prazan.\n");
                break;
        }
    } while(menu_choice!='e');

    return 0;
}
