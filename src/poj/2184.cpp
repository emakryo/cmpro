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
const int Nmax = 100;
const int Offset = 100005;
int N, S[Nmax], F[Nmax];
int dp[2][2*Offset];

int main(){
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		scanf("%d%d", &S[i],&F[i]);
	}

	for(int i=0; i<2*Offset; i++){
		dp[0][i] = dp[1][i] = -1e9;
	}
	dp[1][Offset] = 0;
	for(int i=0; i<N; i++){
		int c = i%2;
		int p = 1-c;
		for(int j=0; j<2*Offset; j++){
			if(dp[p][j] == -1e9) continue;
			dp[c][j] = max(dp[c][j], dp[p][j]);
			dp[c][j+S[i]] = max(dp[c][j+S[i]], dp[p][j]+F[i]);
			//if(Offset-10 <= j && j <= Offset+10) printf("%d %d %d\n", i, j-Offset, dp[c][j]);
		}
	}

	int ans = 0;
	for(int i=0; i<Offset; i++){
		if(dp[N%2][i+Offset] < 0) continue;
		ans = max(ans, dp[(N-1)%2][i+Offset]+i);
		//printf("%d %d\n", i, dp[N%2][i+Offset]);
	}

	printf("%d\n", ans);

	return 0;
}
