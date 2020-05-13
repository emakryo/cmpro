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
vector<vector<int>> divs;

void solve(){
	int n; cin >> n;
	vector<ll> s(n);
	for(int i=0; i<n; i++) cin >> s[i];

	vector<int> dp(n+1, 1);
	for(int i=1; i<=n; i++){
		for(int j: divs[i]){
			if(s[j-1]<s[i-1]) dp[i] = max(dp[i], dp[j]+1);
			dbg(i, j, s[i-1], s[j-1], dp[i], dp[j]+1);
		}
	}
	int ans = 1;
	for(int i=1; i<=n; i++){
		ans = max(ans, dp[i]);
	}
	cout << ans << endl;
}


int main() {
	ios_base::sync_with_stdio(false);

	const int Nmax = 100005;
	divs = vector<vector<int>>(Nmax);

	for(int i=1; i<Nmax; i++){
		for(int k=2; i*k<Nmax; k++) divs[i*k].push_back(i);
	}

	int t; cin >> t;
	for(int i=0; i<t; i++) solve();

	return 0;
}
