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
const int RCmax = 50;
int R, C;
char X[RCmax][RCmax];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

struct edge {
	int to, cap, rev; // destination, capacity, index for reversed edge
};
const int INF = 1e8;

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
	cin >> R >> C;
	for(int i=0; i<R; i++) cin >> X[i];

	FlowGraph g(R*C+2);
	int available = 0;
	int source = R*C;
	int sink = R*C+1;
	for(int i=0; i<R; i++){
		for(int j=0; j<C; j++){
			if(X[i][j] == '*') continue;
			available+=1;
			if((i+j)%2==0){
				g.add_edge(source, i*C+j, 1);
				for(int k=0; k<4; k++){
					int ii = i+dx[k];
					int jj = j+dy[k];
					if(ii<0 || ii>=R || jj<0 || jj>=C) continue;
					if(X[ii][jj] != '.') continue;
					g.add_edge(i*C+j, ii*C+jj, 1);
				}
			}
			else{
				g.add_edge(i*C+j, sink, 1);
			}
		}
	}

	cout << available - g.max_flow(source, sink) << endl;
	return 0;
}
