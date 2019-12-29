#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(any{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

struct mint {
	typedef long long ll;
	ll x, m;
	mint(ll x=0, ll m=1e9+7): x(x%m), m(m) {}
	mint operator-() const { return mint(m-x, m); }
	mint operator+(const mint o) const { return mint(x+o.x, m); }
	mint operator-(const mint o) const { return mint(x-o.x+m, m); }
	mint operator*(const mint o) const { return mint(x*o.x, m); }
	mint& operator+=(const mint o) { x = (x+o.x)%m; return *this; }
	mint& operator-=(const mint o) { x = (x-o.x+m)%m; return *this; }
	mint& operator*=(const mint o) { x = x*o.x%m; return *this; }
	bool operator==(const mint o) const { return x==o.x; }
	bool operator!=(const mint o) const { return x!=o.x; }
	template<typename T> mint& operator=(const T o) { x = o%m; return *this; }
	template<typename T> mint operator+(const T o) const { return mint(x+o, m); }
	template<typename T> mint operator-(const T o) const { return mint(x-((ll)o)%m+m, m); }
	template<typename T> mint operator*(const T o) const { return mint(x*o, m); }
	template<typename T> mint& operator+=(const T o) { x = (x+(ll)o%m)%m; return *this; }
	template<typename T> mint& operator-=(const T o) { x = (x-((ll)o)%m+m)%m; return *this; }
	template<typename T> mint& operator*=(const T o) { x = x*((ll)o%m)%m; return *this; }
	template<typename T> bool operator==(const T o) const { return x==o%m; }
	template<typename T> bool operator!=(const T o) const { return x!=o%m; }

	mint pow(ll k) const {
		if(k==0) return mint(1, m);
		if(k%2) return pow(k-1)*x;
		mint z = pow(k/2);
		return z*z;
	}

	mint inv() const { return pow(m-2); }
};

int N;
void dfs(int u, int p, vector<int> &n_child, vector<vector<int>> &graph){
	int r = 1;
	for(int v: graph[u]){
		if(v==p) continue;
		dfs(v, u, n_child, graph);
		r += n_child[v];
	}
	n_child[u] = r;
}

mint dfs1(int u, int p, vector<int> &n_child, vector<vector<int>> &graph){
	mint r = mint(2).pow(N-1) - 1;
	int sum = 0;
	for(int v: graph[u]){
		if(v == p) continue;
		r -= (mint(2).pow(n_child[v]) - 1);
		sum += n_child[v];
	}
	if(N-sum-1 > 0){
		r -= (mint(2).pow(N-sum-1) - 1);
	}
	debug(u, r.x);
	for(int v: graph[u]){
		if(v == p) continue;
		r += dfs1(v, u, n_child, graph);
	}
	return r;
}

int main(){
	cin >> N;
	vector<vector<int>> graph(N);
	for(int i=0; i<N-1; i++){
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	vector<int> n_child(N);
	dfs(0, -1, n_child, graph);

	debugv(n_child);

	cout << (dfs1(0, -1, n_child, graph) * mint(2).pow(N).inv()).x << endl;;

	return 0;
}
