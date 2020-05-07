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
	vector<pair<ll, ll>> sc(m);
	for(int i=0; i<m; i++){
		string x;
		cin >> x >> sc[i].second;
		for(int j=0; j<n; j++){
			if(x[j]=='Y') sc[i].first+=1<<j;
		}
	}

	vector<ll> dp(1<<n, 1e18);
	dp[0] = 0;
	sort(sc.begin(), sc.end());
	for(int i=0; i<m; i++){
		vector<ll> next(dp);
		for(int j=0; j<(1<<n); j++){
			int k = j|sc[i].first;
			next[k] = min(next[k], dp[j]+sc[i].second);
		}
		dp = next;
	}

	ll ans = dp[(1<<n)-1];
	cout << (ans==1e18?-1:ans) << endl;
	return 0;
}
