#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
typedef vector<boost::variant<bool, ll, int, string, double>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

int main(){
	int N;
	ll K;
	cin >> N >> K;
	vector<ll> A(N);
	for(int i=0; i<N; i++) cin >> A[i];

	vector<ll> hsum(N+1), tsum(N+1);
	hsum[0] = 0;
	for(int i=0; i<N; i++) hsum[i+1] = A[i]+hsum[i];
	tsum[N] = 0;
	for(int i=N-1; i>=0; i--) tsum[i] = A[i]+tsum[i+1];

	vector<vector<ll>> dp(N+1, vector<ll>(N+1, INF));
	for(int i=0; i<=N; i++) dp[i][0] = 0;

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			dp[i+1][j+1] = max(K-tsum[i+1], dp[i][j+1]);
			ll k = max(dp[i][j], K-tsum[i]);;
			if(k < INF){
				ll lb=k, ub=1e9;
				while(ub-lb>1){
					ll med = (lb+ub)/2;
					if(hsum[i]*med > hsum[i+1]*k){
						ub = med;
					} else {
						lb = med;
					}
				}
				if(hsum[i]==0) ub = 1;
				debug(any{hsum[i], ub, hsum[i+1], max(k, K-tsum[i])});
				if(ub<=min(hsum[i+1], K)){
					dp[i+1][j+1] = min(dp[i+1][j+1], max(K-tsum[i+1], ub));
				}
			}
		}
		debug(dp[i+1]);
		debug(any{hsum[i+1], hsum[i]});
	}

	cout << lower_bound(dp[N].begin(), dp[N].end(), INF) - dp[N].begin() -1 << endl;

	return 0;
}
