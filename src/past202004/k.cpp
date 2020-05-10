#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
ostream& operator<<(ostream &os, vector<T> &v){
	string sep = " ";
	if(v.size()) os << v[0];
	for(int i=1; i<v.size(); i++) os << sep << v[i];
	return os;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
	cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__);
#else
#define dbg(...) 
#endif

int main() {
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	string s; cin >> s;
	vector<ll> c(n), d(n);
	for(int i=0; i<n; i++) cin >> c[i];
	for(int i=0; i<n; i++) cin >> d[i];

	const ll INF = 1e18;
	vector<vector<ll>> dp(n+1, vector<ll>(n, INF));

	dp[0][0]=0;
	for(int i=0; i<n; i++){
		for(int k=0; k<n; k++){
			dp[i+1][k] = min(dp[i+1][k], dp[i][k]+d[i]);
			if(s[i]=='('){
				if(k+1<n) dp[i+1][k+1] = min(dp[i+1][k+1], dp[i][k]);
				if(k-1>=0) dp[i+1][k-1] = min(dp[i+1][k-1], dp[i][k]+c[i]);
			} else {
				if(k-1>=0) dp[i+1][k-1] = min(dp[i+1][k-1], dp[i][k]);
				if(k+1<n) dp[i+1][k+1] = min(dp[i+1][k+1], dp[i][k]+c[i]);
			}
		}
	}

	cout << dp[n][0] << endl;


	return 0;
}
