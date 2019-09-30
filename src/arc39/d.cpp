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

template <typename T>
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
		return dist[u]+dist[v]-2*dist[c];
	}
};

void dfs(int u, int p, int &k, vector<vector<int>> &graph, vector<int> &ord, vector<int> &low){
	ord[u] = k++;
	low[u] = ord[u];
	for(int v: graph[u]){
		if(v==p) continue;
		if(ord[v]<0){
			dfs(v, u, k, graph, ord, low);
			low[u] = min(low[u], low[v]);
		} else {
			low[u] = min(low[u], ord[v]);
		}
	}
}

int main(){
	int N, M;
	cin >> N >> M;
	vector<vector<int>> graph(N);
	vector<int> X(M), Y(M);
	for(int i=0; i<M; i++){
		int x, y;
		cin >> x >> y;
		x--; y--;
		graph[x].push_back(y);
		graph[y].push_back(x);
		X[i] = x;
		Y[i] = y;
	}

	vector<int> low(N);
	vector<int> ord(N, -1);
	int k=0;
	dfs(0, -1, k, graph, ord, low);
	debugv(ord);
	debugv(low);
	vector<pair<int, int>> reduced_edges;
	for(int i=0; i<M; i++){
		reduced_edges.push_back({low[X[i]], low[Y[i]]});
	}
	sort(reduced_edges.begin(), reduced_edges.end());
	auto it = unique(reduced_edges.begin(), reduced_edges.end());
	reduced_edges.erase(it, reduced_edges.end());

	LCA<int> lca(N);
	for(auto e: reduced_edges){
		if(e.first != e.second){
			debug(e.first, e.second);
			lca.add_edge(e.first, e.second, 1);
		}
	}
	lca.init();

	int Q;
	cin >> Q;
	for(int i=0; i<Q; i++){
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--; c--;
		debug(low[a], low[b], low[c]);
		debug(lca.distance(low[a], low[b]),lca.distance(low[b], low[c]),lca.distance(low[a], low[c]));
		if(lca.distance(low[a], low[b])+lca.distance(low[b], low[c])==lca.distance(low[a], low[c])){
			cout << "OK" << endl;
		} else {
			cout << "NG" << endl;
		}
	}

	return 0;
}
