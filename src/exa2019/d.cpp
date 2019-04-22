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
const int Nmax = 1e5;
const int P = 1e9+7;
int N, X;
int S[Nmax];

int main(){
	cin >> N >> X;
	for(int i=0; i<N; i++) cin >> S[i];

	sort(S, S+N, greater<int>());
	vector<vector<ll> > dp(N+1, vector<ll>(X+1));
	dp[0][X] = 1;
	for(int i=0; i<N; i++){
		for(int j=0; j<=X; j++){
			dp[i][j] %= P;
			dp[i+1][j%S[i]] += dp[i][j];
			dp[i+1][j] += (N-1-i)*dp[i][j]%P;
		}
	}

	ll ans = 0;
	for(int j=0; j<=X; j++){
		ans = (ans+j*dp[N][j])%P;
	}

	cout << ans << endl;

	return 0;
}
