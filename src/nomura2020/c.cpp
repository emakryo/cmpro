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
	cout << setprecision(20) << fixed;

	int n; cin >> n;
	vector<ll> a(n+1);
	for(int i=0; i<n+1; i++) cin >> a[i];

	vector<ll> v(n+2);
	v[0] = 1;
	const ll INF = 1e18;
	for(int i=0; i<=n; i++){
		v[i+1] = min(INF, 2*(v[i] - a[i]));
		if(v[i+1]<0) {
			cout << -1 << endl;
			return 0;
		}
	}

	ll ans = a[n];
	ll m = a[n];
	for(int i=n-1; i>=0; i--){
		m = min(m + a[i], v[i]);
		ans += m;
	}
	cout << ans << endl;

	return 0;
}
