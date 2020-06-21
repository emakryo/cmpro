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
	vector<int> h(n); cin >> h;
	vector<int> m(n), s(n), e(h);
	for(int i=0; i<n; i++) cin >> m[i] >> s[i] >> e[i];

	vector<tuple<int, int, int>> v(n);
	for(int i=0; i<n; i++){
		get<0>(v[i]) = e[i];
		get<1>(v[i]) = s[i];
		get<2>(v[i]) = m[i];
	}

	sort(v.begin(), v.end());

	vector<ll> dp(n);

	for(int i=0; i<n; i++){
		int k = 0;
		int m = get<2>(v[i]);
		int s = get<1>(v[i]);
		int e = 0;
		ll x = 0;
		for(int j=0; j<i; j++){
			if(get<0>(v[j])<=s) x = max(x, dp[j]);
		}
		for(int j=i; j<n; j++){
			if(get<2>(v[j])!=m) continue;
			if(e<=get<1>(v[j])){
				x += h[k];
				dp[j] = max(dp[j], x);
				k++;
				e = get<0>(v[j]);
			}
		}
	}

	ll ans = 0;
	for(int i=0; i<n; i++){
		ans = max(ans, dp[i]);
	}

	cout << ans << endl;

	return 0;
}
