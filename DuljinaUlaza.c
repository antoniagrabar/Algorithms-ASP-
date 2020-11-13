#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

int binary_search(long c, long t){
	long lo = 0, hi = 1e9;

	while(lo + 1 < hi){
	long mid = (lo+hi)/2;
		if (c*mid*(log(mid)/log(2.0)) < t){
			lo = mid;
		} else {
			hi = mid;
		}
	}

	return lo;

}

int main() {

	int q;
	long c, t;

	scanf("%d\n", &q);

	for (int i = 0; i < q; ++i){
		scanf("%d %d\n", &c, &t);
		printf("%d\n", binary_search(c, t));
	}

	
    return 0;
}
