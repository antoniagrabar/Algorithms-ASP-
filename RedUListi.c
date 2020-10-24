#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

typedef struct Node {
    struct Node *next;
    int val;
} node;

int enqueue(node **head, node **tail, int val) {

    node *newn;
    newn = (node *) malloc(sizeof(node));

    if (!newn) return -1;
    
    newn->val = val;
    newn->next = NULL;

    if (!*head){
        *head = newn;
        *tail = newn;
    } else {
        //elementi postoje, dodajemo na kraj reda
        (*tail)->next = newn;
        *tail = (*tail)->next;
    }

    return 0;
}

int dequeue(node **head, node **tail) {
    if(!*head) return -1;

    if(*head == *tail) *tail = NULL;

    node *tmp = (*head)->next;
    free(*head);
    *head = tmp;

     return 0;
}

/* najmanja slozenost, ispisuje se obrnuto
void reverse_print(node *el){
    if(!el) return;

    reverse_print(el->next);

    printf("%d ", el->val);

}
*/

int print(node *head) {
    node *trenutni;

    if(!head) return -1;

    printf("Red: ");
    for(trenutni=head; trenutni!=NULL; trenutni=trenutni->next) {
        printf("%d ", trenutni->val);
    }
    printf("\n");

    return 0;
}

int main() {
    node *head=NULL, *tail=NULL;
    char menu_choice;
    int val, retval;

    do {
        DEBUG("\n(d) dodaj - enqueue\n(b) brisi - dequeue\n(i) ispis - print\n(e) Exit\n");

        scanf(" %c", &menu_choice);
        switch (menu_choice) {
            case 'd':
                scanf("%d", &val);
                retval = enqueue(&head, &tail, val);
                if (retval==-1) printf("Alokacija nije uspjela.\n");
                break;
            case 'b':
                retval = dequeue(&head, &tail);
                if (retval==-1) printf("Red je prazan.\n");
                break;
            case 'i':
                retval = print(head);
                if (retval==-1) printf("Red je prazan.\n");
                break;
        }
    } while(menu_choice!='e');

    return 0;
}
