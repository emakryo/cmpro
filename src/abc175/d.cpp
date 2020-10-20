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

	int n, k; cin >> n >> k;
	vector<int> p(n); cin >> p;
	vector<ll> c(n); cin >> c;

	for(int i=0; i<n; i++) p[i]--;
	vector<vector<int>> hop(32, vector<int>(n, -1));
	hop[0] = p;
	for(int i=1; i<32; i++){
		for(int j=0; j<n; j++){
			hop[i][j] = hop[i-1][hop[i-1][j]];
		}
		dbg(i, ";", hop[i]);
	}

	vector<vector<ll>> ssum(32, vector<ll>(n));
	for(int i=0; i<n; i++) ssum[0][i] = c[p[i]];
	for(int i=1; i<32; i++){
		for(int j=0; j<n; j++){
			ssum[i][j] = ssum[i-1][j] + ssum[i-1][hop[i-1][j]];
		}
	}

	vector<vector<ll>> smax(32, vector<ll>(n));
	for(int i=0; i<n; i++) smax[0][i] = c[p[i]];
	dbg(0, ";", ssum[0]);
	dbg(0, ";", smax[0]);
	for(int i=1; i<32; i++){
		for(int j=0; j<n; j++){
			smax[i][j] = max(
				ssum[i-1][j] + smax[i-1][hop[i-1][j]],
				smax[i-1][j]
			);
		}
		dbg(i, ";", ssum[i]);
		dbg(i, ";", smax[i]);
	}

	ll ans = -1e9;
	for(int i=0; i<n; i++){
		ll m = -1e15;
		ll s = 0;
		int x = i;
		for(int j=31; j>=0; j--){
			if(k>>j&1){
				m = max(m, smax[j][x] + s);
				s = s + ssum[j][x];
				x = hop[j][x];
			}
		}
		ans = max(ans, m);
	}
	cout << ans << endl;

	return 0;
}
