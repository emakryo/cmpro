#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

int dp[41][401][401];
int main(){
	int N, Ma, Mb;
	cin >> N >> Ma >> Mb;
	vector<int> A(N), B(N), C(N);
	for(int i=0; i<N; i++) cin >> A[i] >> B[i] >> C[i];

	for(int i=0; i<=N; i++) for(int a=0; a<=400; a++) for(int b=0; b<=400; b++){
		dp[i][a][b] = 1e9;
	}
	dp[0][0][0] = 0;

	for(int i=0; i<N; i++) for(int a=0; a<=400; a++) for(int b=0; b<=400; b++){
		dp[i+1][a][b] = dp[i][a][b];
		if(a>=A[i]&&b>=B[i]) dp[i+1][a][b] = min(dp[i][a][b], dp[i][a-A[i]][b-B[i]]+C[i]);
	}

	int ans = 1e9;
	for(int a=1; a<=400; a++) for(int b=1; b<=400; b++){
		if(a*Mb == Ma*b) ans = min(ans, dp[N][a][b]);
	}
	if(ans < 1e9) cout << ans << endl;
	else cout << -1 << endl;

	return 0;
}
