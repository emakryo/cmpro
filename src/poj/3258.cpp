//#include<iostream>
//#include<iomanip>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 500000;
ll L, M, N;
ll D[Nmax+2];

bool possible(ll lower){
	int d = 0;
	int i = 0;
	//printf("%lld\n", lower);
	while(i < N+1){
		int j = 1;
		while(i+j < N+2 && D[i+j]-D[i] < lower) j++;
		d += (j-1);
		//printf("%lld %lld %d %d %d\n", D[i], D[i+j], i, j, d);
		if(d > M) return false;
		i += j;
	}

	return true;
}

int main(){
	scanf("%lld%lld%lld", &L, &N, &M);
	for(int i=0; i<N; i++){
		scanf("%lld", &D[i]);
	}
	D[N] = 0;
	D[N+1] = L;

	sort(D, D+N+2);

	//for(int i=0; i<N+2; i++) printf("%lld\n", D[i]);

	ll lower = 0;
	ll upper = L+1;

	while(upper - lower > 1){
		ll center = (lower+upper)/2;
		if(possible(center)){
			lower = center;
		}
		else{
			upper = center;
		}
	}

	printf("%lld\n", lower);
	return 0;
}
