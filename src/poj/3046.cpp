//#include<iostream>
//#include<iomanip>
#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Tmax = 1000;
int T,A,S,B,X[Tmax];
ll dp[1001][100001];

int main(){
	scanf("%d%d%d%d", &T, &A, &S, &B);
	for(int i=0; i<A; i++){
		int x;
		scanf("%d", &x);
		X[--x]++;
	}

	dp[0][0] = 1;
	for(int i=1; i<=T; i++){
		dp[i][0] = 1;
		for(int j=1; j<=B; j++){
			for(int k=0; k<=X[i-1]; k++){
				if(j-k>=0){
					dp[i][j] += dp[i-1][j-k];
					dp[i][j] %= 1000000;
				}
			}
			//printf("%lld ", dp[i][j]);
		}
		//puts("");
	}

	ll ans = 0;
	for(int i=S; i<=B; i++){
		ans += dp[T][i];
		ans %= 1000000;
	}

	printf("%lld\n", ans);

	return 0;
}
