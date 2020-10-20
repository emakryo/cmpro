#include<bits/stdc++.h>

class MaxFlowGraph{
	using ll = long long;
	const ll INF = 1e18;
	std::vector<bool> used;
	ll dfs(int v, int t, ll f){
		if(v == t) return f;
		used[v] = true;
		for(int i=0; i<graph[v].size(); i++){
			edge &e = graph[v][i];
			if(!used[e.to] && e.cap > 0){
				ll d = dfs(e.to, t, std::min(e.cap, f));
				if(d>0){
					e.cap -= d;
					graph[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}

public:
	struct edge {
		int to, rev; // destination, index for reversed edge
		long long cap; // capacity
	};
	int n;
	std::vector<std::vector<edge> > graph;
	MaxFlowGraph(int n_vertex): n(n_vertex){
		graph.assign(n_vertex, {});
	}

	void add_edge(int from, int to, ll cap){
		graph[from].push_back((edge){to, (int)graph[to].size(), cap});
		graph[to].push_back((edge){from, (int)graph[from].size()-1, 0});
	}

	ll flow(int s, int t){
		ll flow = 0;
		while(true){
			used.assign(n, false);
			ll f = dfs(s, t, INF);
			if(f==0) return flow;
			flow += f;
		}
	}
};
