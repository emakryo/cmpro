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
	ll a, k;
	cin >> a >> k;

	for(int i=1; i<k; i++){
		int dmax = 0;
		int dmin = 10;
		ll x = a;
		while(x>0){
			dmax = max(dmax, int(x%10));
			dmin = min(dmin, int(x%10));
			x /= 10;
		}
		if(dmin==0) break;
		a += dmax*dmin;
	}
	cout << a << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	for(int i=0; i<t; i++) solve();
	return 0;
}
