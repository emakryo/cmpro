#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 100;
const int Mmax = 100000;
int N,M;
int A[Nmax], C[Nmax];
int dp[2][Mmax+1];

int main(){
	while(true){
		scanf("%d%d", &N, &M);
		if(N==0 && M==0) break;
		for(int i=0; i<N; i++){
			scanf("%d", &A[i]);
		}
		for(int i=0; i<N; i++){
			scanf("%d", &C[i]);
		}

		for(int j=1; j<M+1; j++){
			dp[0][j] = dp[1][j] = -1;
		}

		for(int i=0; i<N; i++){
			for(int j=1; j<M+1; j++){
				if(dp[1-i%2][j] >= 0){
					dp[i%2][j] = 0;
				}
				else if(j-A[i] >= 0 && 0 <= dp[i%2][j-A[i]] && dp[i%2][j-A[i]] < C[i]){
					dp[i%2][j] = dp[i%2][j-A[i]]+1;
				}
				printf("%d ", dp[i%2][j]);
			}
			puts("");
		}

		int ans = 0;
		for(int j=1; j<M+1; j++) if(dp[(N-1)%2][j] >= 0){
			ans++;
		}
		printf("%d\n", ans);
	}

	return 0;
}
