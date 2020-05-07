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

void solve(){
	ll n; cin >> n;
	int ans = 0;
	while(n>=2){
		ll lb=1, ub=1e8;
		while(ub-lb>1){
			ll x = (ub+lb)/2;
			if(x*(3*x+1)/2<=n){
				lb = x;
			} else {
				ub = x;
			}
		}
		dbg(lb, lb*(3*lb+1)/2);
		n -= lb*(3*lb+1)/2;
		ans++;
	}
	cout << ans << endl;
}


int main() {
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	for(int i=0; i<t; i++) solve();
	return 0;
}
