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


template<typename T = long long>
struct LCA {
	int n, l, root;
	vector<vector<pair<int, T>>> graph;
	vector<int> dep;
	vector<T> dist;
	vector<vector<int>> par;
	vector<vector<ll>> max_edges;
	LCA(int n) : n(n) {
		l = 0;
		while ((1 << l) < n) l++;
		graph.assign(n, {});
		dist.assign(n, 0);
		dep.assign(n, 0);
		par.assign(n, vector<int>(l, -1));
		max_edges.assign(n, vector<ll>(l));
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
				max_edges[u][i] = std::max(max_edges[u][i-1], max_edges[par[u][i-1]][i-1]);
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
			max_edges[v][0] = cv;
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
	ll max_edge(int from, int to) const {
		// maximum edge between from and to
		// https://atcoder.jp/contests/past202004-open/submissions/13002791
		int u = from;
		ll x = 0;
		for(int i=l-1; i>=0; i--){
			if(par[u][i]<0) continue;
			if(dep[par[u][i]]>=dep[to]){
				x = std::max(x, max_edges[u][i]);
				u = par[u][i];
			}
		}
		return x;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	vector<pair<pair<ll, int>, pair<int, int>>> edge(m);
	for(int i=0; i<m; i++){
		cin >> edge[i].second.first >> edge[i].second.second >> edge[i].first.first;
		edge[i].first.second = i;
	}
	vector<ll> ans(m);
	sort(edge.begin(), edge.end());

	UnionFind uf(n);
	LCA<> lca(n);
	vector<vector<pair<int, ll>>> tree(n);
	vector<bool> use(m);
	ll sum = 0;
	for(int i=0; i<m; i++){
		int a = edge[i].second.first-1;
		int b = edge[i].second.second-1;
		if(uf.same(a, b)) continue;

		ll c = edge[i].first.first;
		sum+=c;
		tree[a].emplace_back(b, c);
		tree[b].emplace_back(a, c);
		uf.unite(a, b);
		use[edge[i].first.second] = true;
		lca.add_edge(a, b, c);
	}
	lca.init();

	vector<ll> max_cost(n);

	for(int i=0; i<m; i++){
		int a = edge[i].second.first-1;
		int b = edge[i].second.second-1;
		int j = edge[i].first.second;
		int c = lca(a, b);
		if(use[j]){
			ans[j] = sum;
		} else {
			ans[j] = sum+edge[i].first.first-max(lca.max_edge(a, c), lca.max_edge(b, c));
		}
	}

	for(int i=0; i<m; i++){
		cout << ans[i] << endl;
	}
	return 0;
}
