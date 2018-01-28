#include<iostream>
#include<vector>
using namespace std;
const int INF = 1e8;

struct edge {
	int to, cap, rev; // destination, capacity, index for reversed edge
};

class FlowGraph{
	vector<vector<edge> > graph;
	int dfs(int v, int t, int f, vector<bool> &used){
		if(v == t) return f;
		used[v] = true;
		for(int i=0; i<graph[v].size(); i++){
			edge &e = graph[v][i];
			if(!used[e.to] && e.cap > 0){
				int d = dfs(e.to, t, min(e.cap, f), used);
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

	void add_edge(int from, int to, int cap){
		graph[from].push_back((edge){to, cap, graph[to].size()});
		graph[to].push_back((edge){from, 0, graph[from].size()-1});
	}

	unsigned int size(){
		return graph.size();
	}

	int max_flow(int s, int t){
		int flow = 0;
		while(true){
			vector<bool> used(size(), false);
			int f = dfs(s, t, INF, used);
			if(f==0) return flow;
			flow += f;
		}
	}

};
