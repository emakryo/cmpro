//#include<iostream>
//#include<iomanip>
#include<cstdio>
#include<cmath>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long ll;
const int Nmax = 10000;
const int Cmax = 10000;
const int STmax = 1 << 16;
const long double PI = 3.141592653589793238L;
int N, C;
int L[Nmax], S[Cmax], A[Cmax];
double vx[STmax], vy[STmax];
double angle[STmax];
int current[Nmax];

void init(int k, int l, int r){
	vx[k] = angle[k] = 0;
	if(r-l == 1) {
		vy[k] = L[l];
	}
	else{
		int m = (l+r)/2;
		init(2*k+1, l, m);
		init(2*k+2, m, r);
		vy[k] = vy[2*k+1] + vy[2*k+2];
	}
}

void update(int s, double a, int k, int l, int r){
	if(l < s && s < r){
		int m = (l+r)/2;
		int cl = 2*k+1;
		int cr = 2*k+2;
		update(s, a, cl, l, m);
		update(s, a, cr, m, r);
		if(s <= m){
			angle[k] += a;
		}
		double co = cos(angle[k]);
		double si = sin(angle[k]);
		vx[k] = vx[cl] + co*vx[cr] - si*vy[cr];
		vy[k] = vy[cl] + si*vx[cr] + co*vy[cr];
	}
}

void solve(){
	init(0, 0, N);
	for(int i=0; i<N; i++){
		current[i] = 180;
	}
	for(int i=0; i<C; i++){
		double a = (A[i]-current[S[i]]) * PI / 180;
		current[S[i]] = A[i];
		update(S[i], a, 0, 0, N);
		printf("%.2f %.2f\n", vx[0], vy[0]);
	}
}

int main(){
	bool first = true;
	while(scanf("%d%d", &N, &C) >= 0){
		if(!first){
			printf("\n");
		}
		else{
			first = false;
		}
		for(int i=0; i<N; i++){
			scanf("%d", &L[i]);
		}
		for(int i=0; i<C; i++){
			scanf("%d%d", &S[i], &A[i]);
		}
		solve();
	}
	return 0;
}
