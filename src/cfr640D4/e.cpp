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
	int n; cin >> n;
	vector<int> a(n);
	for(int i=0; i<n; i++){
		cin >> a[i];
	}

	const int INF=1e9;
	vector<int> b(n+1, -INF);
	vector<vector<int>> c(2, vector<int>(n+1, -INF));
	c[1][0] = 0;
	for(int i=0; i<n; i++){
		c[i%2][0] = 0;
		for(int k=1; k<=n; k++){
			if(k-a[i]>=0) c[i%2][k] = 1+c[1-i%2][k-a[i]];
			else c[i%2][k]=-INF;
			b[k] = max(b[k], c[i%2][k]);
		}
		dbg("c", c[i%2]);
		dbg("b", b);
	}

	int ans = 0;
	for(int i=0; i<n; i++){
		if(b[a[i]]>=2) ans++;
	}
	cout << ans << endl;
}
int main() {
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	for(int i=0; i<t; i++) solve();

	return 0;
}
