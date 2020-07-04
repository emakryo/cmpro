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

	int n, m;
	ll k;
	cin >> n >> m >> k;
	vector<ll> a(n), b(m);
	cin >> a >> b;

	vector<ll> ca(n+1), cb(m+1);
	for(int i=1; i<=n; i++) ca[i] = a[i-1] + ca[i-1];
	for(int i=1; i<=m; i++) cb[i] = b[i-1] + cb[i-1];

	int ans = 0;
	for(int i=0; i<=n; i++){
		if(ca[i]>k) break;
		int j = lower_bound(cb.begin(), cb.end(), k-ca[i]+1) - cb.begin();
		if(j==0){
			if(ca[i]<=k) ans = max(i, ans);
		}
		dbg(i, j, ca[i], cb[j-1]);
		if(ca[i]+cb[j-1]<=k) ans = max(ans, i+j-1);
	}

	cout << ans << endl;

	return 0;
}
