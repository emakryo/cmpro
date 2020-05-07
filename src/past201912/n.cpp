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
	int n, w, c;
	cin >> n >> w >> c;
	vector<int> l(n), r(n);
	vector<ll> p(n);
	for(int i=0; i<n; i++) cin >> l[i] >> r[i] >> p[i];

	vector<pair<int, ll>> lv;
	lv.push_back({w, 0});
	for(int i=0; i<n; i++) lv.push_back({l[i], p[i]});
	sort(lv.begin(), lv.end());
	for(int i=lv.size()-2; i>=0; i--) lv[i].second+=lv[i+1].second;

	vector<pair<int, ll>> rv;
	rv.push_back({0, 0});
	for(int i=0; i<n; i++) rv.push_back({r[i], p[i]});
	sort(rv.begin(), rv.end());
	for(int i=1; i<rv.size(); i++) rv[i].second += rv[i-1].second;

	ll sum = 0;
	for(int i=0; i<n; i++) sum += p[i];
	ll ans = sum;

	for(int i=0; i<rv.size(); i++){
		if(rv[i].first+c>w) break;
		auto lb = lower_bound(lv.begin(), lv.end(), pair<int, ll>{c+rv[i].first, 0ll});
		dbg(rv[i].first, rv[i].second, lb->first, lb->second);
		ans = min(ans, sum-rv[i].second-lb->second);
	}
	cout << ans << endl;
	return 0;
}
