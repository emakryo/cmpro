#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Tmax = 1000;
int T, W, A[Tmax];
int dp[2][32][2];

int main(){
	scanf("%d%d", &T, &W);
	for(int i=0; i<T; i++){
		scanf("%d", &A[i]);
		A[i]--;
	}

	for(int j=0; j<=W; j++){
		dp[0][j][0] = dp[0][j][1] = -1e8;
		dp[1][j][0] = dp[1][j][1] = -1e8;
	}
	dp[1][0][0] = 0;
	for(int i=0; i<T; i++){
		for(int j=0; j<=W; j++){
			dp[i%2][j][0] = max(dp[1-i%2][j][0]+(1-A[i]), dp[1-i%2][j-1][1]+(1-A[i]));
			dp[i%2][j][1] = max(dp[1-i%2][j-1][0]+A[i], dp[1-i%2][j][1]+A[i]);
			//printf("%d %d\n", dp[i%2][j][0], dp[i%2][j][1]);
		}
		//puts("");
	}

	int ans = 0;
	for(int j=0; j<=W; j++){
		ans = max(ans, dp[0][j][0]);
		ans = max(ans, dp[0][j][1]);
		ans = max(ans, dp[1][j][0]);
		ans = max(ans, dp[1][j][1]);
	}

	printf("%d\n", ans);

	return 0;
}
