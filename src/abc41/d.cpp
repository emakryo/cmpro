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
	int n, m; cin >> n >> m;
	vector<int> x(m), y(m);
	vector<vector<bool>> a(n, vector<bool>(n));
	for(int i=0; i<m; i++){
		cin >> x[i] >> y[i];
		x[i]--; y[i]--;
		a[x[i]][y[i]] = true;
	}

	vector<ll> dp(1<<n);
	dp[0] = 1;

	for(int s=0; s<(1<<n); s++){
		for(int i=0; i<n; i++){
			if(s>>i&1) continue;
			bool ok = true;
			for(int j=0; j<n; j++){
				if((s>>j&1)&&(a[i][j])) ok = false;
			}
			if(ok){
				dp[s|(1<<i)] += dp[s];
			}
		}
	}

	cout << dp[(1<<n)-1] << endl;

	return 0;
}
