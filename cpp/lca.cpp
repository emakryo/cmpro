#include <bits/stdc++.h>
using namespace std;

template<typename T = long long>
struct LCA {
	int n, l, root=-1;
	vector<vector<pair<int, T>>> graph;
	vector<int> dep;
	vector<T> dist;
	vector<vector<int>> par;
	vector<vector<T>> max_edges;
	LCA(int n) : n(n) {
		l = 0;
		while ((1 << l) < n) l++;
		graph.assign(n, {});
		dist.assign(n, 0);
		dep.assign(n, 0);
		par.assign(n, vector<int>(l, -1));
		max_edges.assign(n, vector<T>(l));
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
		assert(root>=0); // check whether inited
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
	T max_edge(int from, int to) const {
		// maximum edge between from and to
		// https://atcoder.jp/contests/past202004-open/submissions/13002791
		assert(root>=0); // check whether inited
		int u = from;
		T x = 0;
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
