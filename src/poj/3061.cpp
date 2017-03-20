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

int main(){
	int T;
	scanf("%d", &T);
	for(int t=0; t<T; t++){
		int N;
		ll S;
		scanf("%d%lld", &N, &S);
		vector<ll> X(N);
		for(int i=0; i<N; i++) scanf("%lld", &X[i]);
		
		ll sum=0;
		int p=0, q=0;
		int ans=N+1;
		while(q<=N){
			//printf("%d %d %lld\n", p, q, sum);
			if(sum<S){
				sum += X[q++];
			}
			else{
				ans = min(ans, q-p);
				sum -= X[p++];
			}
		}

		printf("%d\n", ans<N+1 ? ans : 0);
	}
	return 0;
}
