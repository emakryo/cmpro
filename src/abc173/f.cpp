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

	int n; cin >> n;
	vector<pair<int, int>> es(n-1);
	for(int i=0; i<n-1; i++){
		int u, v;
		cin >> u >> v;
		es[i] = {u, v};
	}

	ll ans = 0;
	for(ll i=0; i<n; i++){
		ans += (n-i+1)*(n-i)/2;
	}

	for(int i=0; i<n-1; i++){
		int u = es[i].first;
		int v = es[i].second;
		ans -= (ll)min(u, v) * (n+1-max(u, v));
	}
	cout << ans << endl;

	return 0;
}
