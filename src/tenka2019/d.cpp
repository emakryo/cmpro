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
const ll P = 998244353;
int N;
const int Nmax = 300;
int A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];
	int S = 0;
	for(int i=0; i<N; i++) S += A[i];

	vector<vector<ll> > dp(N+1, vector<ll>(S+1));
	for(int i=0; i<=N; i++) dp[i][0] = 1;
	for(int i=0; i<N; i++){
		for(int j=0; j<=S; j++){
			dp[i+1][j] = 2*dp[i][j];
			if(j>=A[i]) dp[i+1][j] += dp[i][j-A[i]];
			dp[i+1][j] %= P;
		}
	}
	vector<vector<ll> > dp1(N+1, vector<ll>(S+1));
	for(int i=0; i<=N; i++) dp1[i][0] = 1;
	for(int i=0; i<N; i++){
		for(int j=0; j<=S; j++){
			dp1[i+1][j] = dp1[i][j];
			if(j>=A[i]) dp1[i+1][j] += dp1[i][j-A[i]];
			dp1[i+1][j] %= P;
		}
	}
	//for(int j=0; j<=N; j++) for(int i=0; i<=S; i++) cout << dp[j][i] << (i==S?'\n':' ');
	//for(int j=0; j<=N; j++) for(int i=0; i<=S; i++) cout << dp1[j][i] << (i==S?'\n':' ');

	ll ans = 1;
	for(int i=0; i<N; i++) ans = 3*ans%P;
	ll x = 0;
	for(int i=(S+1)/2; i<=S; i++) x += dp[N][i];
	if(S%2==0) x = (x-dp1[N][S/2]+P)%P;
	//cout << x << " " << dp1[N][S/2] << endl;
	ans = (ans - 3*x%P + P) % P;
	cout << ans << endl;

	return 0;
}
