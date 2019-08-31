#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Nmax = 100;
const ll INF=1e16;
int N;
ll W, Ws[Nmax], Vs[Nmax];
ll dp[Nmax+1][Nmax+1][4*Nmax];

int main(){
	cin >> N >> W;
	for(int i=0; i<N; i++) cin >> Ws[i] >> Vs[i];

	for(int i=0; i<=N; i++){
		for(int k=0; k<=N; k++){
			for(int w=0; w<4*N; w++){
				dp[i][k][w] = -INF;
			}
		}
	}
	dp[0][0][0] = 0;

	for(int i=0; i<N; i++){
		for(int k=0; k<=N; k++){
			for(int w=0; w<4*N; w++){
				dp[i+1][k][w] = dp[i][k][w];
				if(w>0) dp[i+1][k][w] = max(dp[i+1][k][w-1], dp[i+1][k][w]);
				if(k>0&&w-(Ws[i]-Ws[0])>=0){
					dp[i+1][k][w] = max(dp[i+1][k][w], dp[i][k-1][w-(Ws[i]-Ws[0])]+Vs[i]);
				}
				//cout << i << " " << k << " " << w << " " << dp[i+1][k][w] << endl;
			}
		}
	}

	ll ans = 0;
	for(int k=0; k<=N; k++){
		//cout << min(4ll*N, max(0ll, W-k*Ws[0])) << endl;
		if(W-k*Ws[0]>=0) ans = max(ans, dp[N][k][min(4ll*N-1, W-k*Ws[0])]);
	}
	cout << ans << endl;

	return 0;
}
