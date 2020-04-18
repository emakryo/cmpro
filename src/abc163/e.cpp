#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> anys;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(anys{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

int main(){
	int N;
	cin >> N;
	vector<ll> A(N);
	for(int i=0; i<N; i++) cin >> A[i];

	vector<pair<ll, int>> ai(N);
	for(int i=0; i<N; i++) ai[i]={A[i], i};
	sort(ai.rbegin(), ai.rend());
	vector<vector<ll>> dp(N+1, vector<ll>(N+1));
	for(int i=0; i<N; i++) for(int k=0; k<=i; k++){
		int l = N-i+k-1;
		dp[i+1][k] = max(dp[i+1][k], dp[i][k] + ai[i].first * abs(ai[i].second - l));
		dp[i+1][k+1] = max(dp[i+1][k+1], dp[i][k] + ai[i].first * abs(ai[i].second - k));
		debug(i, k, N-i+k-1, dp[i+1][k], dp[i+1][k+1]);
	}

	ll ans = 0;
	for(int k=0; k<=N; k++){
		ans = max(ans, dp[N][k]);
	}
	cout << ans << endl;

	return 0;
}
