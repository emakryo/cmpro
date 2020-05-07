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

struct DGraph{
	typedef std::vector<std::vector<std::pair<int, ll>>> G;
	typedef std::vector<bool> vb;
	typedef std::vector<int> vi;
	int n;
	G g;
	DGraph(int n):n(n), g(G(n)){}

	void add_edge(int from, int to, ll weight=1){
		g[from].emplace_back(to, weight);
	}

	std::vector<int> toposort() const {
		vi order;
		vb done(n);
		vb visit(n);
		for(int i=0; i<n; i++){
			if(done[i]) continue;
			if(toposort_rec(i, visit, done, order)){
				return vi();
			}
		}
		reverse(order.begin(), order.end());
		return order;
	}

	bool toposort_rec(int u, vb &visit, vb &done, vi &order) const {
		if(visit[u]) return true;
		if(done[u]) return false;
		done[u] = true;
		visit[u] = true;
		for(auto v: g[u]){
			if(toposort_rec(v.first, visit, done, order)) return true;
		}
		visit[u]=false;
		order.push_back(u);
		return false;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	DGraph graph(n), rgraph(n);
	for(int i=0; i<m; i++){
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph.add_edge(a, b);
		rgraph.add_edge(b, a);
	}

	vector<int> topo = graph.toposort();
	vector<int> rtopo = rgraph.toposort();
	if(topo.size()==0||rtopo.size()==0) {
		cout << -1 << endl;
		return 0;
	}

	vector<int> midx(n, n), rmidx(n, n);
	for(int u: topo){
		midx[u] = min(midx[u], u);
		for(auto v: graph.g[u]){
			midx[v.first] = min(midx[v.first], midx[u]);
		}
	}

	for(int u: rtopo){
		rmidx[u] = min(rmidx[u], u);
		for(auto v: rgraph.g[u]){
			rmidx[v.first] = min(rmidx[v.first], rmidx[u]);
		}
	}

	vector<bool> va(n);
	int ans = 0;
	for(int i=0; i<n; i++){
		if(midx[i]>=i&&rmidx[i]>=i){
			ans++;
			va[i] = true;
		}
	}

	cout << ans << endl;
	for(int i=0; i<n; i++) cout << (va[i]?"A":"E");
	cout << endl;

	return 0;
}
