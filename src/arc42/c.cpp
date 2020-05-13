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
#define dbg(...) debug_(__VA_ARGS__)
#else
#define dbg(...) 
#endif

int main() {
	ios_base::sync_with_stdio(false);
	int n, p;
	cin >> n >> p;
	vector<pair<int, int>> ab(n);
	for(int i=0; i<n; i++) cin >> ab[i].first >> ab[i].second;

	sort(ab.rbegin(), ab.rend());

	const int INF=1e9;
	vector<vector<int>> dp(n+1, vector<int>(p+200, -INF));
	dp[0][0] = 0;

	for(int i=0; i<n; i++){
		for(int j=0; j<p+200; j++){
			dp[i+1][j] = dp[i][j];
			if(j-ab[i].first>=0) dp[i+1][j] = max(dp[i][j], dp[i][j-ab[i].first]+ab[i].second);
		}

		for(int j=1; j<p+200; j++){
			dp[i+1][j] = max(dp[i+1][j], dp[i+1][j-1]);
		}
	}

	int ans = 0;
	for(int i=0; i<n; i++){
		dbg(ab[i].first, ab[i].second, dp[i+1][p+ab[i].first]);
		ans = max(ans, dp[i+1][p+ab[i].first]);
	}
	cout << ans << endl;

	return 0;
}
