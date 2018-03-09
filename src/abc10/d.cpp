#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const int INF = 1e8;
int N, G, E, P[100];
int A[100000], B[100000];

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

int main(){
	cin >> N >> G >> E;
	for(int i=0; i<G; i++) cin >> P[i];
	for(int i=0; i<E; i++) cin >> A[i] >> B[i];

	FlowGraph g(N+1);
	for(int i=0; i<E; i++){
		g.add_edge(A[i], B[i], 1);
		g.add_edge(B[i], A[i], 1);
	}
	for(int i=0; i<G; i++){
		g.add_edge(P[i], N, 1);
	}

	cout << g.max_flow(0, N) << endl;

	return 0;
}
