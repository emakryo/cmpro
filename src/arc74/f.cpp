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
const int Hmax = 100;
int H, W;
string A[Hmax];

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

int main(){
	cin >> H >> W;
	for(int i=0; i<H; i++) cin >> A[i];

	FlowGraph flow(2*H*W+H+W);

	int s, t;
	for(int x=0; x<H; x++){
		for(int y=0; y<W; y++){
			if(A[x][y]=='.') continue;
			if(A[x][y]=='S') s = y*H+x;
			if(A[x][y]=='T') t = y*H+x;
			flow.add_edge(y*H+x+H*W, y*H+x, 1);
			//cout << y*H+x+H*W << " " <<  y*H+x << endl;

			flow.add_edge(y*H+x, 2*H*W+x, INF);
			flow.add_edge(y*H+x, 2*H*W+H+y, INF);
			//cout << y*H+x << " " << 2*H*W+x << endl;
			//cout << y*H+x << " " << 2*H*W+H+y << endl;

			flow.add_edge(2*H*W+x, y*H+x+H*W, INF);
			flow.add_edge(2*H*W+H+y, y*H+x+H*W, INF);
			//cout << 2*H*W+x << " " << y*H+x+H*W << endl;
			//cout << 2*H*W+H+y << " " << y*H+x+H*W << endl;
		}
	}

	//cout << s << " " <<  t+H*W << endl;
	if(s/H==t/H || s%H==t%H) cout << -1 << endl;
	else cout << flow.max_flow(s, t+H*W) << endl;

	return 0;
}
