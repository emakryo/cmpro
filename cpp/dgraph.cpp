#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

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
		vb done(n), visit(n);
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
		done[u] = visit[u] = true;
		for(auto v: g[u]){
			if(toposort_rec(v.first, visit, done, order)) return true;
		}
		visit[u]=false;
		order.push_back(u);
		return false;
	}
};
