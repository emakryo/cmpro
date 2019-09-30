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

template<typename T = long long>
struct LCA {
	int n, l, root;
	vector<vector<pair<int, T>>> graph;
	vector<int> dep;
	vector<T> dist;
	vector<vector<int>> par;
	LCA(int n) : n(n) {
		l = 0;
		while ((1 << l) < n) l++;
		graph.assign(n, {});
		dist.assign(n, 0);
		dep.assign(n, 0);
		par.assign(n, vector<int>(l, -1));
	}
	void add_edge(int u, int v, T c = 0) {
		graph[u].emplace_back(v, c);
		graph[v].emplace_back(u, c);
	}
	void init(int _root = 0) {
		root = _root;
		dfs(root, -1, 0, 0);
		for (int i=1; i<l; i++) {
			for (int u=0; u<n; u++) {
				if (par[u][i-1] < 0) continue;
				par[u][i] = par[par[u][i-1]][i-1];
			}
		}
	}
	void dfs(int u, int p, T c, int d) {
		dist[u] = c;
		par[u][0] = p;
		dep[u] = d;
		for (auto e : graph[u]) {
			int v = e.first;
			T cv = e.second;
			if (v==p) continue;
			dfs(v, u, c+cv, d+1);
		}
	}
	int operator() (int u, int v) const {
		if (dep[u]<dep[v]) swap(u, v);
		int gap = dep[u]-dep[v];
		for (int i=0; i<l; i++) {
			if (gap & (1 << i)) u = par[u][i];
		}
		if (u==v) return u;
		for (int i=l-1; i>=0; i--) {
			if (par[u][i]!=par[v][i]) {
				u = par[u][i];
				v = par[v][i];
			}
		}
		return par[u][0];
	}
	T distance(int u, int v) const {
		int c = (*this)(u, v);
		if(c < 0) return -1; // when graph is not connected
		return dist[u]+dist[v]-2*dist[c];
	}
};

struct LowLink {
	int n;
	vector<vector<int>> graph;
	vector<int> used, ord, low;
	vector<bool> articulation;
	set<pair<int, int>> bridge;

	LowLink(int n): n(n) {
		graph.assign(n, {});
	}
	void add_edge(int u, int v){
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	int dfs(int u, int p, int k) {
		used[u] = true;
		ord[u] = k++;
		low[u] = ord[u];
		int cnt = 0;
		for(int v : graph[u]) {
			if(!used[v]) {
				++cnt;
				k = dfs(v, u, k);
				low[u] = min(low[u], low[v]);
				articulation[u] = articulation[u] ||(~p && low[v] >= ord[u]);
				if(ord[u] < low[v]) bridge.insert(minmax(u, v));
			} else if(v != p) {
				low[u] = min(low[u], ord[v]);
			}
		}
		articulation[u] = articulation[u] || (p == -1 && cnt > 1);
		return k;
	}
	void build() {
		used.assign(n, 0);
		ord.assign(n, 0);
		low.assign(n, 0);
		articulation.assign(n, false);
		int k = 0;
		for(int i = 0; i < n; i++) {
			if(!used[i]) k = dfs(i, -1, k);
		}
	}
};

struct UnionFind{
	std::vector<int> par, rnk, cnt;
	UnionFind(int n){
		par.assign(n, 0);
		rnk.assign(n, 0);
		cnt.assign(n, 1);
		for(int i=0; i<n; i++) par[i]=i;
	}
	int root(int i){
		if(par[i]==i) return i;
		return par[i]=root(par[i]);
	}
	void unite(int i, int j){
		int ri = root(i);
		int rj = root(j);
		if(ri==rj) return;

		if(rnk[ri]==rnk[rj]){
			cnt[rj] += cnt[ri];
			par[ri] = rj;
			rnk[rj]++;
		}
		else if(rnk[ri] < rnk[rj]){
			cnt[rj] += cnt[ri];
			par[ri] = rj;
		}
		else{
			cnt[ri] += cnt[rj];
			par[rj] = ri;
		}
	}
	bool same(int i, int j){
		return root(i) == root(j);
	}
	int count(int i){
		return cnt[root(i)];
	}
};

int main(){
	int N, M;
	cin >> N >> M;
	vector<int> X(M), Y(M);
	for(int i=0; i<M; i++){
		int x, y;
		cin >> x >> y;
		x--; y--;
		if(x>y) swap(x, y);
		X[i] = x;
		Y[i] = y;
	}

	LowLink lowlink(N);
	for(int i=0; i<M; i++) lowlink.add_edge(X[i], Y[i]);
	lowlink.build();

	UnionFind uf(N);
	for(int i=0; i<M; i++){
		if(lowlink.bridge.count({X[i], Y[i]})==0) uf.unite(X[i], Y[i]);
	}

	LCA<> lca(N);
	for(int i=0; i<M; i++){
		if(!uf.same(X[i], Y[i])){
			debug(uf.root(X[i]), uf.root(Y[i]));
			lca.add_edge(uf.root(X[i]), uf.root(Y[i]), 1);
		}
	}
	lca.init(uf.root(0));

	int Q;
	cin >> Q;
	for(int i=0; i<Q; i++){
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--; c--;
		a = uf.root(a);
		b = uf.root(b);
		c = uf.root(c);
		debug(a, b, c);
		ll x = lca.distance(a, b);
		ll y = lca.distance(b, c);
		ll z = lca.distance(a, c);
		debug(x, y, z);
		if(x + y == z){
			cout << "OK" << endl;
		} else {
			cout << "NG" << endl;
		}
	}

	return 0;
}
