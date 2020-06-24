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

template<typename T>
istream& operator>>(istream &is, vector<T> &v){
	for(int i=0; i<v.size(); i++) is >> v[i];
	return is;
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
	cout << setprecision(20) << fixed;
	int n, m; cin >> n >> m;
	vector<int> a(n), b(m);
	cin >> a >> b;

	vector<vector<int>> dp(n+1, vector<int>(m+1));

	vector<int> ca(n), cb(m);
	ca[0] = a[0];
	cb[0] = b[0];
	for(int i=1; i<n; i++) ca[i] = ca[i-1]+a[i];
	for(int i=1; i<m; i++) cb[i] = cb[i-1]+b[i];

	for(int i=0; i<n; i++){
		dp[i+1][0] = dp[i][0];
		if((n+m-i-1)%2==0) dp[i+1][0] += a[n-1-i];
		dbg(i+1, 0, dp[i+1][0]);
	}
	for(int i=0; i<m; i++){
		dp[0][i+1] = dp[0][i];
		if((n+m-i-1)%2==0) dp[0][i+1] += b[m-1-i];
		dbg(0, i+1, dp[0][i+1]);
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if((n+m-i-1-j-1)%2==0){
				dp[i+1][j+1] = max(dp[i][j+1]+a[n-1-i], dp[i+1][j]+b[m-1-j]);
			} else {
				dp[i+1][j+1] = min(dp[i][j+1], dp[i+1][j]);
			}
			dbg(i+1, j+1, dp[i+1][j+1], a[n-1-i], b[m-1-j]);
		}
	}

	cout << dp[n][m] << endl;

	return 0;
}
