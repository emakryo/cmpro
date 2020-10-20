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

	int nr, nc, k; cin >> nr >> nc >> k;
	vector<vector<ll>> v(nr, vector<ll>(nc));

	for(int i=0; i<k; i++){
		int r, c, vi;
		cin >> r >> c >> vi;
		r--; c--;
		v[r][c] = vi;
	}

	vector<vector<vector<ll>>> dp(nr+1, vector<vector<ll>>(nc+1, vector<ll>(4)));

	for(int i=0; i<nr; i++) for(int j=0; j<nc; j++) for(int m=0; m<4; m++) {
		dp[i+1][j+1][m] = dp[i+1][j][m];
		if(m>0) dp[i+1][j+1][m] = max(dp[i+1][j+1][m], dp[i+1][j][m-1] + v[i][j]);
		if(m==0) dp[i+1][j+1][0] = max(dp[i+1][j+1][0], *max_element(dp[i][j+1].begin(), dp[i][j+1].end()));
		if(m==1) dp[i+1][j+1][1] = max(dp[i+1][j+1][1], *max_element(dp[i][j+1].begin(), dp[i][j+1].end()) + v[i][j]);
		if(m==3) dbg(i, j, dp[i+1][j+1]);
	}

	cout << *max_element(dp[nr][nc].begin(), dp[nr][nc].end()) << endl;
	return 0;
}
