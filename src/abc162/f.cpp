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

ll INF = 1e18;
int main(){
	int N;
	cin >> N;
	vector<ll> A(N);
	for(int i=0; i<N; i++) cin >> A[i];

	vector<vector<ll>> dp(N+1, vector<ll>(6));
	dp[0][0] = -INF;
	dp[0][1] = 0;
	dp[0][2] = -INF;
	dp[0][3] = -INF;
	dp[0][4] = -INF;
	dp[0][5] = -INF;

	for(int i=1; i<=N; i++){
		if(i%2){
			dp[i][0] = max(dp[i-1][0], dp[i-1][3]);
			dp[i][1] = max(dp[i-1][1], dp[i-1][4]);
			dp[i][2] = max(dp[i-1][2], dp[i-1][5]);
			dp[i][3] = -INF;
			dp[i][4] = A[i-1] + dp[i-1][0];
			dp[i][5] = A[i-1] + dp[i-1][1];
		} else {
			dp[i][0] = max(dp[i-1][1], dp[i-1][4]);
			dp[i][1] = max(dp[i-1][2], dp[i-1][5]);
			dp[i][2] = -INF;
			dp[i][3] = A[i-1] + dp[i-1][0];
			dp[i][4] = A[i-1] + dp[i-1][1];
			dp[i][5] = A[i-1] + dp[i-1][2];
		}
		debug(i, dp[i][0], dp[i][1], dp[i][2], dp[i][3], dp[i][4], dp[i][5]);
	}

	cout << max(dp[N][1], dp[N][4]) << endl;

	return 0;
}
