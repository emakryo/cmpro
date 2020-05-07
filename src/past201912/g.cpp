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

vector<vector<ll>> a;

ll dfs(int i, vector<vector<int>> &x){
	int n=a.size();
	if(i==n){
		ll ret = 0;
		for(int j=0; j<3; j++){
			for(int k=0; k<x[j].size(); k++){
				for(int l=k+1; l<x[j].size(); l++){
					ret+=a[x[j][k]][x[j][l]];
				}
			}
		}
		return ret;
	}
	ll ret = -1e18;
	for(int j=0; j<3; j++){
		x[j].push_back(i);
		ret = max(ret, dfs(i+1, x));
		x[j].pop_back();
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	a = vector<vector<ll>>(n, vector<ll>(n));
	for(int i=0; i<n-1; i++){
		for(int j=i+1; j<n; j++){
			int x;
			cin >> x;
			a[i][j] = a[j][i] = x;
		}
	}
	for(int i=0; i<n; i++) dbg(a[i]);

	vector<vector<int>> x(3);
	cout << dfs(0, x) << endl;

	return 0;
}
