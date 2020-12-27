#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

//0-indeksirano
#define PARENT(i) ((i-1)/2)


void check_heap(int *array, int size){
    int fMin = 1;
    int fMax = 1;

    for (int i = size-1; i > 0; i--){
        //ne radi se o max heapu
        if(array[i] > array[PARENT(i)]){
            fMax = 0;
        }

        //ne radi se o min heapu
        if(array[i] < array[PARENT(i)]){
            fMin = 0;
        }
    }

    if(!fMin && !fMax){
        printf("NO-HEAP\n");
    } else if(fMin && !fMax){
        printf("MIN-HEAP\n");
    } else if(!fMin && fMax){
        printf("MAX-HEAP\n");
    } else {
        printf("HEAP\n");
    }
}

int main() {
    int menu_choice, i, num, len=0, *array=NULL;
    char c;

    setbuf(stdout, NULL);
    do {
        //DEBUG("\n1 opis funkcije (ime_funkcije)");
        DEBUG("\n2.Unos niza\n3.Izlaz\n");
        scanf("%d", &menu_choice);
        switch(menu_choice) {
            case 1:
                check_heap(array, len);
                break;
            case 2:
                DEBUG("\nUnesite broj elemenata niza: ");
                scanf("%d", &len);
                DEBUG("\nUnesite elemente niza: ");
                if (array) free(array);
                array = malloc(len*sizeof(int));
                for (i=0; i<len; i++) {
                    scanf("%d", &num);
                    array[i] = num;
                }
                DEBUG("\nUneseni niz:\n");
                for (i=0; i<len; i++) {
                    DEBUG("%d ", array[i]);
                }
                DEBUG("\n");
                break;
            case 3:
                break;
            default:
                while((c=getchar())!='\n' && c!=EOF);
        }
    } while(menu_choice!=3);
    return 0;
}
