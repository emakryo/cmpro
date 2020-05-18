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
	int n; cin >> n;
	ll a, r, m; cin >> a >> r >> m;
	m = min(m, a+r);
	vector<ll> h(n);
	for(int i=0; i<n; i++) cin >> h[i];
	sort(h.begin(), h.end());

	ll ans = 1e18;
	ll sum = 0;
	for(int i=1; i<n; i++) sum += h[i]-h[0];

	ll p = 0, q=sum;
	for(int i=0; i<n; i++){
		dbg(p, q);
		if(p<q){
			ans = min(ans, m*p+r*(q-p));
		} else {
			ans = min(ans, m*q+a*(p-q));
		}
		if(i<n-1){
			p += (i+1)*(h[i+1]-h[i]);
			q -= (n-i-1)*(h[i+1]-h[i]);
		}
	}

	for(int l=0; l<2; l++){
		ll g=h[0]+sum/n+l;
		p=0;
		q=0;
		for(int i=0; i<n; i++){
			if(h[i]<g) p+= g-h[i];
			else q += h[i]-g;
		}
		if(p<q){
			ans = min(ans, m*p+r*(q-p));
		} else {
			ans = min(ans, m*q+a*(p-q));
		}
	}

	cout << ans << endl;

	return 0;
}
