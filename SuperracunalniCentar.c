#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAXN 100000

void quick_sort(int a[], int l, int r){
	int pivot_index = (l+r)/2;

	swap(&a[pivot_index], &a[r]);
	int pivot_value = a[r];

	int i = l-1;
	for(int j = l; j < r; j++){
		if(a[j] <= pivot_value){
			i++;
			swap(&a[j], &a[i]);
		}
	}
	swap(&a[++i], &a[r]);

	if(i > l){
		quick_sort(a, l, i-1);
	}

	if(i < r){
		quick_sort(a, i+1, r);
	}
}

void swap(int *a, int *b){
	int t= *a;
	*a = *b;
	*b = t;
}

int binary_search(int a[], int n, int tmp){
	int lo = -1, hi = n;

	while(lo + 1 < hi){
		int mid = (lo+hi)/2;
		if(a[mid] <= tmp){
			lo = mid;
		} else {
			hi = mid;
		}
	}

	return hi;
}

int main() {

	int n, q, tmp, price[MAXN];

	scanf("%d", &n);

	for (int i = 0; i < n; ++i){
		scanf("%d ", &price[i]);
	}

	quick_sort(price, 0, n-1);

	scanf("%d", &q);
	for (int i = 0; i < q; ++i){
		scanf("%d\n", &tmp);
		printf("%d\n", binary_search(price, n, tmp));
	}
}