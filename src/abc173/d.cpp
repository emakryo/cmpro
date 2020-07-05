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
	vector<ll> a(n); cin >> a;
#ifdef DBG
	n = 200000;
	a = vector<ll>(n, 1);
#endif

	sort(a.rbegin(), a.rend());

	ll ans = 0;
	vector<ll> x(1, a[0]), y;
	for(int i=1; i<n; i++){
		int k=y.size();
		ans += min(x[k], x[(k+1)%x.size()]);
		y.push_back(a[i]);
		if(x.size()==y.size()){
			vector<ll> z;
			for(int i=0; i<x.size(); i++){
				z.push_back(x[i]);
				z.push_back(y[i]);
			}
			x=z;
			y.clear();
		}
	}

	cout << ans << endl;


	return 0;
}
