#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAXN 100000


/*pronalazi indeks zadnje dionice u polju 'time' za koju vrijedi da
je razlika vremena njene kupnje i vremena kupljene dionice u trenutku
k manja od dopustene razlike 'due_date'*/ 

int latest_sale(int time[], int due_date, int k, int trans_num){

	int lo = k, hi = trans_num;

	while(lo+1 < hi){
		int mid = (lo+hi)/2;
		if (time[mid] - time[k] > due_date){
			hi = mid;
		} else {
			lo = mid;
		}
	}

	return lo;
}

int main() {

	int trans_num, due_date, time[MAXN], price[MAXN], max_profit = 0;

	scanf("%d %d", &trans_num, &due_date);

	for (int i = 0; i < trans_num; ++i){
		scanf("%d %d\n", &time[i], &price[i]);
	}

	for(int k = 0; k < trans_num-1; k++){
		int p = latest_sale(time, due_date, k, trans_num);
		int missed_profit = price[p] - price[k];
		if(missed_profit > max_profit) max_profit = missed_profit;
	}

	printf("%d", max_profit);
}