#include <stdio.h>
#include <math.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define EPS 1e-10

int eval(double mid, double V){
	double v0 = 10 * cos(mid + 2) * log(mid + 2) + 10.877;

	if(V > v0){
		return 1;
	} else {
		return 0;
	}
}

double ventil(double V) {
	double lo = 0;
	double hi = 1;
	double mid;

	while(lo + EPS < hi){
		mid = (hi + lo)/2;

		if(eval(mid, V)){
			hi = mid;
		} else {
			lo = mid;
		}

	}

	return hi; 

}

int main() {
  int n, i;
  double V;
  scanf("%d", &n);
  for (i = 0; i < n; ++i) {
    scanf("%lf", &V);
    printf("%.6f\n", ventil(V));
  }
  return 0;
}
