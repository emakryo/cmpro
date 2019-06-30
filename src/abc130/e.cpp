#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const int Nmax = 2e3;
const ll P = 1e9+7;
int N, M, S[Nmax], T[Nmax];

int main(){
	cin >> N >> M;
	for(int i=0; i<N; i++) cin >> S[i];
	for(int i=0; i<M; i++) cin >> T[i];

	vector<vector<ll> > dp(N+1, vector<ll>(M+1));
	for(int i=0; i<=N; i++) dp[i][0] = 1;
	for(int i=0; i<=M; i++) dp[0][i] = 1;

	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			dp[i+1][j+1] = dp[i+1][j] + dp[i][j+1];
			if(S[i]!=T[j]){
				dp[i+1][j+1] += P-dp[i][j];
			}
			dp[i+1][j+1] %= P;
		}
	}

	cout << dp[N][M] << endl;

	return 0;
}
