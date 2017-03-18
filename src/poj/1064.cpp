#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const int Nmax = 10000;
int N, K;
double L[Nmax];

int main(){
	scanf("%d%d", &N, &K);
	for(int i=0; i<N; i++){
		scanf("%lf", &L[i]);
	}

	double upper=1e8, lower=0;
	for(int i=0; i<100; i++){
		double med = (upper+lower)/2;
		int m = 0;
		for(int i=0; i<N; i++) m += floor(L[i]/med);
		if(m >= K) lower = med;
		else upper = med;
	}

	printf("%.2f\n", floor(100*lower)/100);

	return 0;
}
