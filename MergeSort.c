#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

void merge(int array[], int temp[], int left_start, int right_pos, int right_end){
	//right_pos je mid+1

	int left_end = right_pos-1;
	int left_pos = left_start;
	int temp_pos = left_start;

	while((left_pos <= left_end) && (right_pos <= right_end)){
		if(array[left_pos] <= array[right_pos]){
			//uzimamo lijevi element
			temp[temp_pos++] = array[left_pos++];
		} else {
			//uzimamo desni element
			temp[temp_pos++] = array[right_pos++];
		}
	}	

	//prebaciti elemente s kraja jednog od nizova na kraj tempa
	while(left_pos <= left_end){
		temp[temp_pos++] = array[left_pos++];
	}

	while(right_pos <= right_end){
		temp[temp_pos++] = array[right_pos++];
	}

	/*
	//kopiramo nazad u glavno polje, od kraja prema pocetku
	right_pos = right_end;
	while(right_pos >= left_start){
		array[right_pos] = temp[right_pos];
		--right_pos;
	}
	*/

	//isto ko gornja while petlja
	for (int i = right_end; i >= left_start; i--){
		array[i] = temp[i];
	}
}

void merge_sort(int array[], int temp[], int left, int right){
	if (right > left){ //right==left bazicni slucaj
		int mid = (right + left)/2;

		merge_sort(array, temp, left, mid);
		merge_sort(array, temp,  mid+1, right);
		merge(array, temp, left, mid+1, right);
	
	}
}

void print(int array[], int  n){
	for (int i = 0; i < n; ++i){
		printf("%d ", array[i] );
	}
	printf("\n");
}

int main() {
	int n, *array, *temp;

	scanf("%d", &n);

	array = malloc(n * sizeof(int));
	temp = malloc(n * sizeof(int));

	for (int i = 0; i < n; ++i){
		scanf("%d", array + i);
	}

	merge_sort(array, temp, 0, n-1);
	print(array, n);

	free(array);
	free(temp);

	return 0;
}