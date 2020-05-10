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
	ll n;
	int m;
	cin >> n >> m;
	vector<ll> x(m);
	for(int i=0; i<m; i++) cin >> x[i];
	if(n==m){
		cout << 0 << endl;
		return 0;
	}

	ll lb=0, ub=1e10;
	while(ub-lb>1){
		ll z = (lb+ub)/2;
		ll p = 0;
		for(int i=0; i<m; i++){
			if(x[i]-z-p>1){
				p=0;
				break;
			}
			p = min(p, x[i]-1);
			p = max(x[i], max(z-x[i]+2*p+2, (z+x[i]+p+1)/2));
			dbg(z, i, p);
		}
		if(p>=n){
			ub = z;
		} else {
			lb = z;
		}
	}

	cout << ub << endl;

	return 0;
}
