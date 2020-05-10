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
	vector<ll> a(n);
	for(int i=0; i<n; i++) cin >> a[i];

	sort(a.rbegin(), a.rend());
	map<ll, int> cnt;
	for(ll x: a) cnt[x]++;
	vector<bool> use(n);

	int ans = 0;
	for(int i=0; i<n; i++){
		ll x = a[i];
		for(int k=32; k>=0; k--){
			ll y = 1ll<<k;
			if(cnt.count(x)==0||cnt[x]==0) break;
			if(y <= x) break;
			if(2*x==y){
				if(cnt[x]>1){
					cnt[x]-=2;
					ans++;
					dbg(x, y);
					if(cnt[x]==0) cnt.erase(x);
				}
			} else if(cnt.count(y-x)>0&&cnt[y-x]>0){
				cnt[y-x]--;
				cnt[x]--;
				if(cnt[y-x]==0) cnt.erase(y-x);
				if(cnt[x]==0) cnt.erase(x);
				dbg(x, y);
				ans++;
			}
		}
	}

	cout << ans << endl;
	return 0;
}
