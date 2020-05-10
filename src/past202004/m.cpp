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

	int d, n;
	ll l;
	cin >> d >> l >> n;
	vector<int> c(d), k(n), f(n);
	vector<ll> t(n);
	for(int i=0; i<d; i++) cin >> c[i];
	for(int i=0; i<n; i++) cin >> k[i] >> f[i] >> t[i];

	const int C = 100005;
	vector<vector<int>> idx(C);
	for(int i=0; i<d; i++) {
		idx[c[i]].push_back(i);
	}

	vector<vector<int>> cum(C);
	for(int i=0; i<C; i++){
		int m = idx[i].size();
		if(m==0) continue;

		for(int j=0; j<m; j++){
			cum[i].push_back((j>0?cum[i][j-1]:0) + (idx[i][(j+1)%m]-idx[i][j%m]+(j==m-1?d:0)+l-1)/l);
		}
		dbg(i, idx[i]);
		dbg(i, cum[i]);

	}

	for(int i=0; i<n; i++){
		vector<int> kidx = idx[k[i]];
		int m = kidx.size();
		if(m==0){
			cout << 0 << endl;
			continue;
		}

		ll ans = 0;
		int lb = lower_bound(kidx.begin(), kidx.end(), f[i]-1)-kidx.begin();
		if(lb==m){
			t[i]-=(kidx[0]+d-f[i]+1+l-1)/l;
			lb = 0;
		} else {
			t[i]-=(kidx[lb]-f[i]+1+l-1)/l;
		}
		dbg(i, t[i], lb);
		if(t[i]<=0){
			cout << 0 << endl;
			continue;
		}
		if(lb>0){
			t[i]+=cum[k[i]][lb-1];
			ans-=lb;
		}
		dbg(i, t[i], ans);
		ans += t[i]/cum[k[i]][m-1]*m;
		t[i]%=cum[k[i]][m-1];

		if(t[i]>0){
			int x = lower_bound(cum[k[i]].begin(), cum[k[i]].end(), t[i])-cum[k[i]].begin();
			dbg(i, t[i], x);

			ans += x+1;
		}
		cout << ans << endl;
	}

	return 0;
}
