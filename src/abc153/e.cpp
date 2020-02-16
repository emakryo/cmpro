#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(any{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

ll dp[1000+5][20000+5];
int main(){
	int H, N;
	cin >> H >> N;
	vector<int> A(N), B(N);
	for(int i=0; i<N; i++) cin >> A[i] >> B[i];

	for(int i=0; i<N; i++){
		dp[i][0] = 0;
		for(int j=0; j<20000+5; j++){
			if(j>0) dp[i][j] = 1e18;
			if(i>0) dp[i][j] = min(dp[i][j], dp[i-1][j]);
			if(j-A[i]>=0) dp[i][j] = min(dp[i][j], dp[i][j-A[i]]+B[i]);
			if(j < 110) debug(i, j, dp[i][j]);
		}
	}

	ll ans = 1e18;
	for(int j=H; j<20000+5; j++){
		ans = min(ans, dp[N-1][j]);
	}
	cout << ans << endl;

	return 0;
}
