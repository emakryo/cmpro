#include<bits/stdc++.h>
typedef std::vector<std::vector<std::pair<int, long long>>> Graph;

/*
	Topological sort.
	If graph is not a DAG, return empty list.
*/
std::vector<int> toposort(Graph &graph) {
	int n = graph.size();
	std::vector<int> order;
	std::vector<bool> done(n), visit(n);
	for(int i=0; i<n; i++){
		if(done[i]) continue;
		if(toposort_rec(i, graph, visit, done, order)){
			return std::vector<int>();
		}
	}
	reverse(order.begin(), order.end());
	return order;
}

bool toposort_rec(int u, Graph &g, std::vector<bool> &visit, std::vector<bool> &done, std::vector<int> &order) {
	if(visit[u]) return true;
	if(done[u]) return false;
	done[u] = visit[u] = true;
	for(auto v: g[u]){
		if(toposort_rec(v.first, g, visit, done, order)) return true;
	}
	visit[u]=false;
	order.push_back(u);
	return false;
}
