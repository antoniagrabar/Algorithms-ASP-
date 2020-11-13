#include <stdio.h>
#include <math.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif


int binary_search(long c, long t) {

  long lo = 0, hi = 1e9;

  while (lo + 1 < hi) {
    long mid = (hi + lo)/2;
		if (c*mid*log(mid)/log(2.0) > t ) {
	      hi = mid;
	    } else {
	      lo = mid;
	    }
  }
  
  return lo;
}

int main() {
  long c, t, q, i;

  scanf("%d", &q);
  for (i = 0; i < q; ++i) {
    scanf("%d %d", &c, &t);
    printf("%d\n", binary_search(c, t));
  }
  return 0;
}
