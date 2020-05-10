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
	int n, m;
	cin >> n>> m;
	vector<string> a(n);
	int s, g;
	for(int i=0; i<n; i++){
		cin >> a[i];
		for(int j=0; j<m; j++){
			if(a[i][j]=='S'){
				a[i][j]='0';
				s=i*m+j;
			}

			if(a[i][j]=='G'){
				a[i][j]='9'+1;
				g=i*m+j;
			}
		}
	}

	const ll INF = 1e18;
	vector<vector<pair<int, ll>>> graph(n*m);
	vector<ll> dist(n*m, INF);
	dist[s] = 0;
	for(int k=0; k<10; k++){
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				if(a[i][j]!=k+'0') continue;
				for(int ni=0; ni<n; ni++){
					for(int nj=0; nj<m; nj++){
						if(a[ni][nj]!=k+'1') continue;
						dist[ni*m+nj] = min(dist[ni*m+nj], dist[i*m+j]+abs(i-ni)+abs(j-nj));
						dbg(i, j, ni, nj, dist[ni*m+nj]);
					}
				}
			}
		}
	}

	if(dist[g]<INF){
		cout << dist[g] << endl;
	} else {
		cout << -1 << endl;
	}

	return 0;
}
