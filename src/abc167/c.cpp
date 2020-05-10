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
	int n, m, x; cin >> n >> m >> x;
	vector<int> c(n);
	vector<vector<int>> a(n, vector<int>(m));
	for(int i=0; i<n; i++){
		cin >> c[i];
		for(int j=0; j<m; j++) cin >> a[i][j];
	}

	const int INF=1e9;
	int ans = INF;
	for(int s=0; s<(1<<n); s++){
		int sum = 0;
		vector<int> z(m);
		for(int k=0; k<n; k++){
			if((s>>k&1)==0) continue;
			for(int j=0; j<m; j++){
				z[j]+=a[k][j];
			}
			sum+=c[k];
		}
		dbg(z);
		bool ok = true;
		for(int k=0; k<m; k++){
			if(z[k]<x) ok = false;
		}
		if(ok) ans = min(ans, sum);
	}
	cout << (ans<INF?ans:-1) << endl;
	return 0;
}
