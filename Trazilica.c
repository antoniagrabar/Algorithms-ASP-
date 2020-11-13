#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAXN 100000

int binary_search(int a[], int k, int tmp){
	int lo = -1, hi = k;
	while(lo + 1 < hi){
		int mid = (lo + hi)/2;
		if (a[mid] < tmp){
			lo = mid;
		} else {
			hi = mid;
		}
	}
	return hi;
}

int main() {

	int n, k, q;
	int deleted_pages[MAXN+1];

	scanf("%d %d\n", &n, &k);
	for (int i = 0; i < k; ++i){
		scanf("%d ", &deleted_pages[i]);
	}
	scanf("%d", &q);
	for (int i = 0; i < q; ++i){
		int tmp;
		scanf("%d", &tmp);
		printf("%d\n", tmp - binary_search(deleted_pages, k, tmp));
	}
}