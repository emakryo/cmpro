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
	int n; cin>>n;
	vector<ll> c(n);
	for(int i=0; i<n; i++) cin >> c[i];
	int q; cin >> q;

	vector<ll> ce((n+1)/2), co(n/2);
	ll me=c[0], mo=1e14;
	for(int i=0; i<n; i++){
		if(i%2){
			co[i/2]=c[i];
			mo = min(mo, c[i]);
		} else{
			ce[i/2]=c[i];
			me = min(me, c[i]);
		}
	}
	ll be=0, bo=0;
	ll ans = 0;
	for(int qi=0; qi<q; qi++){
		int s;
		int x;
		ll a;
		cin >> s;
		if(s==1){
			cin >> x >> a;
			x--;
			if(x%2){
				if(co[x/2]+bo>=a){
					co[x/2]-=a;
					mo = min(mo, co[x/2]+bo);
					ans += a;
				}
			} else {
				if(ce[x/2]+be>=a){
					ce[x/2]-=a;
					me = min(me, ce[x/2]+be);
					ans += a;
				}
			}
		} else if(s==2){
			cin >> a;
			if(me>=a){
				be-=a;
				me-=a;
				ans += a*ce.size();
			}
		} else {
			cin >> a;
			if(me>=a&&mo>=a){
				be-=a;
				me-=a;
				bo-=a;
				mo-=a;
				ans += a*n;
			}
		}
		dbg(qi, me, mo, ans);
	}

	cout << ans << endl;
	return 0;
}
