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

	ll a;
	int n, m;
	cin >> a >> n >> m;
	vector<ll> l(n), x(m), y(m);
	for(int i=0; i<n; i++) cin >> l[i];
	for(int i=0; i<m; i++) cin >> x[i] >> y[i];

	vector<ll> d;
	for(int i=0; i<n-1; i++) d.push_back(l[i+1]-l[i]-1);
	sort(d.begin(), d.end());

	vector<ll> c;
	if(n>1){
		c.push_back(d[0]);
		for(int i=1; i<d.size(); i++){
			c.push_back(c.back()+d[i]);
		}
	}

	dbg(d);
	dbg(c);

	for(int i=0; i<m; i++){
		ll ans = n + min(l[0]-1, x[i]) + min(a-l[n-1], y[i]);

		int k = lower_bound(d.begin(), d.end(), x[i]+y[i]) - d.begin();

		ans += (x[i]+y[i])*(n-1-k);
		if(k>0) ans += c[k-1];
		dbg(i, n, min(l[0]-1, x[i]), min(a-l[n-1], y[i]), k, (x[i]+y[i])*(n-1-k), c[k-1]);
		cout << ans << endl;
	}

	return 0;
}
