#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif


int push(int stack[], int *top, int val, int *tt) {
    if(*top==SIZE-1) return -1;

    (*top)++;
    if (*top+1>*tt) *tt = *top+1; //gledamo *top+1 jer trebamo broj elemenata, a ne index zadnjeg
    stack[*top] = val;

    return 0;
}

int pop(int stack[], int *top) {
    if(*top==-1) return -1;

    (*top)--;
    return 0;
}

int print(int stack[], int top) {
    int i;

    if(top==-1) return -1;

    for(i=top; i>=0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");
    return 0;
}


void top_topova(int tt) {
    printf("%d\n", tt);
}

int main() {
    int val, ret_val, menu_choice, tt=0;
    int *stack, top = -1;
    char c;

    setbuf(stdout, NULL);
    stack = (int *)malloc(sizeof(int) * SIZE);
    do {
        menu_choice = 0;
 
        scanf("%d", &menu_choice);
        switch (menu_choice) {
            case 1:
                top_topova(tt);
                break;
            case 2:
                scanf("%d", &val);
                ret_val = push(stack, &top, val, &tt);
                if(ret_val==-1) DEBUG("Stog je pun.\n");
                break;
            case 3:
                ret_val = pop(stack, &top);
                if(ret_val==-1) DEBUG("Stog je prazan.\n");
                break;
            case 4:
                ret_val = print(stack, top);
                if(ret_val==-1) DEBUG("Stog je prazan.\n");
                break;
            case 5:
                break;
            default:
                while((c = getchar()) != '\n' && c != EOF);
        }
    } while(menu_choice!=5);

    free(stack);
    return 0;
}