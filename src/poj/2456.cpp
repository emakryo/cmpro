//#include<iostream>
//#include<iomanip>
#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const int Nmax = 100000;
ll X[Nmax];
int N, C;

int main(){
	scanf("%d%d", &N, &C);
	for(int i=0; i<N; i++) scanf("%lld", &X[i]);

	sort(X, X+N);
	ll lower = 0;
	ll upper = 1e9;
	while(upper-lower > 1){
		int last = 0;
		int count = 1;
		ll med = (lower+upper)/2;
		for(int i=0; i<N; i++){
			if(X[i] >= X[last]+med){
				last = i;
				count++;
				//printf("%lld %d\n", med, count);
			}
		}
		if(count >= C){
			lower = med;
		}
		else{
			upper = med;
		}
	}

	printf("%lld\n", lower);

	return 0;
}
