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

int main(){
	int N; cin >> N;
	vector<vector<int>> graph(N);
	LCA<int> lca(N);
	for(int i=0; i<N-1; i++){
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
		lca.add_edge(a, b, 1);
	}

	lca.init();
	int M; cin >> M;
	vector<pair<int, int>> path(M);
	for(int i=0; i<M; i++){
		cin >> path[i].first >> path[i].second;
		path[i].first--; path[i].second--;
	}
	vector<vector<bool>> used(M, vector<bool>(N));
	for(int i=0; i<M; i++){
		int anc = lca(path[i].first, path[i].second);
		int u = path[i].first;
		while(u != anc){
			used[i][u] = true;
			u = lca.par[u][0];
		}
		u = path[i].second;
		while(u != anc) {
			used[i][u] = true;
			u = lca.par[u][0];
		}
	}

	ll ans = 0;
	for(int s=0; s<1<<M; s++){
		vector<bool> used_or(N);
		int ns = 0;
		for(int i=0; i<M; i++){
			if(((s>>i)&1)==0) continue;
			for(int j=0; j<N; j++){
				used_or[j] = used_or[j] || used[i][j];
			}
			ns++;
		}
		int ne = 0;
		for(int j=0; j<N; j++) if(used_or[j]) ne++;
		debug(s, ns, ne, 1<<(N-1-ne));
		ans += (1-2*(ns%2))*(1ll<<(N-1-ne));
	}

	cout << ans << endl;

	return 0;
}
