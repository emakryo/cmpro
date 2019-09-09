#include <bits/stdc++.h>
#include <boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template <typename T>
inline void pr(const vector<T> &xs) {
	for (int i = 0; i < xs.size() - 1; i++) cout << xs[i] << " ";
	(xs.empty() ? cout : (cout << xs[xs.size() - 1])) << endl;
}
template <typename T>
inline void debug(const vector<T> &xs) {
#ifdef DEBUG
	pr(xs);
#endif
}

template <typename T>
struct LCA {
	int n, l, root;
	vector<vector<pair<int, T>>> graph;
	vector<int> dep;
	vector<T> dist;
	vector<vector<int>> par;
	LCA(int n) : n(n) {
		l = 0;
		while ((1 << l) < n)
			l++;
		graph.assign(n, {});
		dist.assign(n, 0);
		dep.assign(n, 0);
		par.assign(n, vector<int>(l));
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

struct Query {
	int qid;
	int color;
	int coeff;
};

struct Edge {
	int to;
	int color;
	int cost;
};

vector<ll> ans;
vector<vector<Edge>> graph;
vector<vector<Query>> qsum, qnum;
vector<ll> sum, num;
void dfs(int u, int p)
{
	for (auto q : qsum[u]) ans[q.qid] += q.coeff * sum[q.color];
	for (auto q : qnum[u]) ans[q.qid] += q.coeff * num[q.color];
	for (auto e : graph[u]) {
		if (e.to == p) continue;
		sum[e.color] += e.cost;
		num[e.color] += 1;
		dfs(e.to, u);
		sum[e.color] -= e.cost;
		num[e.color] -= 1;
	}
}

int main() {
	int N, Q;
	cin >> N >> Q;
	LCA<ll> lca(N);
	graph.assign(N, {});
	for (int i = 0; i < N - 1; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		a--; b--;
		lca.add_edge(a, b, d);
		graph[a].push_back({b, c, d});
		graph[b].push_back({a, c, d});
	}
	lca.init();
	qsum.assign(N, {});
	qnum.assign(N, {});
	sum.assign(N, 0);
	num.assign(N, 0);
	ans.assign(Q, 0);
	for (int i = 0; i < Q; i++) {
		int x, y, u, v;
		cin >> x >> y >> u >> v;
		u--; v--;
		int c = lca(u, v);
		ans[i] = lca.distance(u, v);
		debug(any{ans[i], c});
		qsum[u].push_back({i, x, -1});
		qsum[v].push_back({i, x, -1});
		qsum[c].push_back({i, x, 2});
		qnum[u].push_back({i, x, y});
		qnum[v].push_back({i, x, y});
		qnum[c].push_back({i, x, -2*y});
	}
	dfs(0, -1);

	for(int i=0; i<Q; i++){
		cout << ans[i] << endl;
	}

	return 0;
}
