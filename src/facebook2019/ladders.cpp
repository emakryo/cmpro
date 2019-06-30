#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const int Nmax = 50;
int N, H, X[Nmax], A[Nmax], B[Nmax];
const ll INF = 1e18;

struct edge {
	int to, rev; // destination, index for reversed edge
	ll cap; //capacity
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
		graph[to].push_back((edge){from, (int)graph[from].size()-1, 0ll});
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

ll solve(){
	cin >> N >> H;
	for(int i=0; i<N; i++){
		cin >> X[i] >> A[i] >> B[i];
		X[i]++;
	}

	vector<pair<int, pair<int, int>>> ladder;
	for(int i=0; i<N; i++){
		if(A[i]==0&&B[i]==H){
			return -1;
		}
		ladder.push_back({X[i], {A[i], B[i]}});
	}
	sort(ladder.begin(), ladder.end());

	vector<pair<int, pair<int, int>>> xs;
	vector<vector<pair<int, int>>> graph(N+2);
	for(int i=0; i<N; i++){
		int a = ladder[i].second.first;
		int b = ladder[i].second.second;
		if(a==0){
			graph[N].push_back({i, 1e8});
		}
		if(b==H){
			graph[i].push_back({N+1, 1e8});
		}
		vector<pair<int, pair<int, int>>> ys;
		ys.push_back({i, {a, b}});
		for(auto x: xs){
			int n = x.first;
			int xa = x.second.first;
			int xb = x.second.second;
			int w = min(xb, b) - max(xa, a);
			if(w>0){
				graph[n].push_back({i, w});
				graph[i].push_back({n, w});
			}
			if(xa < a && b < xb){
				ys.push_back({n, {xa, a}});
				ys.push_back({n, {b, xb}});
			} else if(xa < a){
				ys.push_back({n, {xa, min(a, xb)}});
			} else if(b < xb){
				ys.push_back({n, {max(b, xa), xb}});
			}
		}
		xs = ys;
	}

	FlowGraph flow(N+2);
	for(int i=0; i<N+2; i++){
		for(auto es: graph[i]){
			//cout << i << " " << es.first << " " << es.second << endl;
			flow.add_edge(i, es.first, es.second);
		}
	}

	return flow.max_flow(N, N+1);
}

int main(){
	int T;
	cin >> T;
	for(int i=0; i<T; i++){
		cout << "Case #" << i+1 << ": " << solve() << endl;
	}

	return 0;
}
