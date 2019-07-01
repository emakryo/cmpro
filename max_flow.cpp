#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;
const ll INF = 1e18;

struct edge {
	int to, rev; // destination, index for reversed edge
	ll cap; // capacity
};

class FlowGraph{
	vector<vector<edge> > graph;
	ll dfs(int v, int t, ll f, vector<bool> &used){
		if(v == t) return f;
		used[v] = true;
		for(int i=0; i<graph[v].size(); i++){
			edge &e = graph[v][i];
			if(!used[e.to] && e.cap > 0){
				ll d = dfs(e.to, t, min(e.cap, f), used);
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
	FlowGraph(int n_vertex){
		graph = vector<vector<edge> >(n_vertex);
	}

	void add_edge(int from, int to, ll cap){
		graph[from].push_back((edge){to, (int)graph[to].size(), cap});
		graph[to].push_back((edge){from, (int)graph[from].size()-1, 0});
	}

	unsigned int size(){
		return graph.size();
	}

	ll max_flow(int s, int t){
		ll flow = 0;
		while(true){
			vector<bool> used(size(), false);
			ll f = dfs(s, t, INF, used);
			if(f==0) return flow;
			flow += f;
		}
	}

};
