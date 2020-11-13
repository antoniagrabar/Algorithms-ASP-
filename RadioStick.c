#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

int binary_search(int array[], int n, int q){
	int hi = n;
	int lo = -1;
	int mid;

	while(lo+1 < hi){
		mid = (lo+hi)/2;

		if (q <= array[mid]){
			hi = mid;
		} else {
			lo = mid;
		}
	}

	return hi;


}

/*

1 - 1 2
2 - 3 4 5 6 7 8 9
3 - 10 11 12
4 - 13 - 16
5 - 17 - 25

  L H
2 9 12 16 25
F F T  T  T
q=11
*/

int main() {
	int n, m, q, array[100000];

	scanf("%d", &n);

	for (int i = 0; i < n; ++i){
		scanf("%d", &array[i]);

		if (i>0){
			array[i] += array[i-1];
		}
	}

	scanf("%d", &m);

	for (int i = 0; i < m; ++i){
		scanf("%d", &q);

		printf("%d\n", binary_search(array,n,q)+1);
	}


}