#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif


void quick_sort(int array[], int l, int r){

	int pivot_index = (l+r)/2;

	swap(&array[pivot_index], &array[r]); //stavi pivota na zadnje mjesto
	int pivot_value = array[r];

	//partitioning
	int i = l-1; // i je brojac
	for(int j = l; j < r; j++){
		if(array[j] <= pivot_value){
			i++;
			swap(&array[i], &array[j]);
		}
	}
	swap(&array[++i], &array[r]); //stavi pivota na svoje pravo mjesto


	if(i > l){
		quick_sort(array, l, i-1);
	}

	if(i < r){
		quick_sort(array, i+1, r);
	}

}

void swap(int *a, int *b){
	int t= *a;
	*a = *b;
	*b = t;
}

void print(int array[], int  n){
	for (int i = 0; i < n; ++i){
		printf("%d ", array[i] );
	}
	printf("\n");
}

int main() {
	int n, *array;

	scanf("%d", &n);

	array = malloc(n * sizeof(int));

	for (int i = 0; i < n; ++i){
		scanf("%d", array + i);
	}

	quick_sort(array, 0, n-1);

	print(array, n);

	free(array);

	return 0;
}