#include<stdio.h>
#include<stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAX_SIZE 100000

int pronadji_samca(int *array, int len) {

    int lo = -1, hi = len-1;

    //ako je mid neparan, a sljedeci element je isti, samac je s lijeve strane -> hi = mid
    //ako je mid paran, a sljedeci element nije isti, to je trazeni samac -> hi = mid, hi se vise nece pomaknut
    while(lo+1 < hi){
        int mid = (lo+hi)/2;
        if ((mid&2!=0 && array[mid]==array[mid+1]) || (mid%2==0 && array[mid]!=array[mid+1])){
            hi = mid;
        } else {
            lo = mid;
        }
    }

    return array[hi];
}

int main() {
    int array[MAX_SIZE];
    int menu_choice, len = 0;
    char c;

    setbuf(stdout, NULL);
    do {
        DEBUG("\n1 Pronadji samca (pronadji_samca)");
        DEBUG("\n2.Unos elemenata u polje\n");
        scanf("%d", &menu_choice);

        switch(menu_choice) {
            case 1:
                for (int i=0; i<1000; ++i) pronadji_samca(array, len);
                printf("%d\n", pronadji_samca(array, len));
                break;
            case 2:
                DEBUG("Unos zakljucite bilo kojim nebrojcanim znakom: ");
                len = 0;
                while(scanf("%d", array+len)==1) len++;
                while((c=getchar())!='\n' && c!=EOF);
                break;
            case 3:
                break;
            default:
                while((c=getchar())!='\n' && c!=EOF);
        }
    } while(menu_choice!=3);
    return 0;
}
