#include <stdio.h>


#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define EPS 1e-10

int pretpostavka(double mid, double iznos, double rata, double rok){
	//vraca 0 ako je stopa preniska
	//vraca 1 ako je stopa previsoka
	double rj;

	for (int i = 0; i < rok; ++i){
		rj = iznos + iznos*mid - rata;
		iznos = rj;
	}

	if (iznos > 0){
		return 1;
	} else {
		return 0;
	}

}

double kamatna_stopa(double iznos, double rata, double rok) {
	double lo = 0, hi = 500000, mid;

	while(lo + EPS < hi){
		mid = (lo+hi)/2;
		if (pretpostavka(mid, iznos, rata, rok)){
			hi = mid;
		} else {
			lo = mid;
		}
	}

	return mid;
}


int main() {
  double k, r, m;
  scanf("%lf%lf%lf", &k, &r, &m);
  printf("%.6f", kamatna_stopa(k, r, m)*100*12);
  return 0;
}
