#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

typedef struct Node {
    struct Node *next;
    int val;
} node;

int add(node **head, int val) {
    node *new;
    new = (node *) malloc(sizeof(node));
    if (!new) return -1;

    new->val = val;
    new->next = *head;
    *head = new;
    return 0;
}

//-2 element nije nađen
//-1 lista prazna 
//0 nađen i uspješno obrisan

int delete(node **head, int val) {

    if(!*head) return -1;

    node *trenutni, *prethodni;
    prethodni = *head;

    for(trenutni = *head; trenutni!= NULL; trenutni = trenutni->next){
        if(trenutni->val == val){
            if(trenutni == *head){
                *head = trenutni->next;
            } else {
                prethodni->next = trenutni->next;
            }
            free(trenutni);
            return 0;
        }
        prethodni = trenutni;
    }

    return -2;
}   


int print(node *head) {
    node *trenutni;

    if (!head) return -1;

    printf("Lista: ");
    for (trenutni=head; trenutni!=NULL; trenutni=trenutni->next) {
        printf("%d ", trenutni->val);
    }
    printf("\n");

    return 0;
}

int main() {
    node *head=NULL;
    char menu_choice;
    int val, retval;

    do {
        DEBUG("\n(d) dodaj - add\n(b) brisi - delete\n(i) ispis - print\n(e) Exit\n");

        scanf(" %c", &menu_choice);
        switch (menu_choice) {
            case 'd':
                scanf("%d", &val);
                retval = add(&head, val);
                if (retval==-1) printf("Alokacija nije uspjela.\n");
                break;
            case 'b':
                scanf("%d", &val);
                retval = delete(&head, val);
                if (retval==-1) printf("Lista je prazna.\n");
                else if (retval==-2) printf("Element nije nadjen.\n");
                break;
            case 'i':
                retval = print(head);
                if (retval==-1) printf("Lista je prazna.\n");
                break;
        }
    } while(menu_choice!='e');

    return 0;
}
