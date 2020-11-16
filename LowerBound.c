#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

int lower_bound(int *a, int len, int v) {

  int lo = -1, hi = len, mid;

  while(lo+1 < hi){
    mid = (hi+lo)/2;

    if (a[mid] >= v){
      hi = mid;
    } else {
      lo = mid;
    }
  }

  return hi;
}

int main() {
  int n, q, v, a[100001], i;
  scanf("%d %d", &n, &q);
  for (i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (i = 0; i < q; ++i) {
    scanf("%d", &v);
    printf("%d\n", lower_bound(a, n, v));
  }
  return 0;
}
