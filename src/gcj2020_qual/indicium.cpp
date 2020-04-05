#include<bits/stdc++.h>
//#define epr(...) fprintf(stderr, __VA_ARGS__);
#define epr(...) while(0) {}
using namespace std;
typedef long long ll;

struct edge {
	int to, rev; // destination, index for reversed edge
	ll cap; // capacity
};

struct FlowGraph{
	const ll INF = 1e18;
	int n;
	std::vector<std::vector<edge> > graph;
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

	FlowGraph(int n_vertex): n(n_vertex){
		graph.assign(n_vertex, {});
	}

	void add_edge(int from, int to, ll cap){
		graph[from].push_back((edge){to, (int)graph[to].size(), cap});
		graph[to].push_back((edge){from, (int)graph[from].size()-1, 0});
	}

	ll max_flow(int s, int t){
		ll flow = 0;
		while(true){
			used.assign(n, false);
			ll f = dfs(s, t, INF);
			if(f==0) return flow;
			flow += f;
		}
	}

};

bool solve1(int a, int b, int c, int N){
	vector<vector<int>> mat(N, vector<int>(N));
	vector<vector<bool>> used(N, vector<bool>(N));
	used[b-1][0] = true;
	used[c-1][1] = true;
	for(int r=2; r<N; r++) used[a-1][r] = true;

	for(int r=0; r<N; r++){
		FlowGraph flow(2*N+2);
		int s=2*N, t=2*N+1;
		for(int i=0; i<N; i++){
			flow.add_edge(s, i, 1);
			flow.add_edge(i+N, t, 1);
		}
		for(int c=0; c<N; c++){
			if(c==r) continue;
			for(int i=0; i<N; i++){
				if(!used[i][c]) flow.add_edge(c, i+N, 1);
			}
		}
		int diag = a-1;
		if(r==0) diag = b-1;
		if(r==1) diag = c-1;
		flow.add_edge(r, diag+N, 1);
		ll f = flow.max_flow(s, t);
		epr("f: %i\n", f);

		for(int c=0; c<N; c++){
			for(edge e: flow.graph[c]){
				if(N<=e.to&&e.to<2*N){
					epr("%i %i %i %i\n", r, c, e.to-N, e.cap);
					if(e.cap==0){
						mat[r][c] = e.to-N;
						used[e.to-N][c] = true;
					}
				}
			}
		}

		if(f<N){
			return false;
		}
	}

	printf("POSSIBLE\n");
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			printf("%i%s", mat[i][j]+1, j==N-1?"\n":" ");
		}
	}
	return true;
}

void solve(){
	int N, K;
	cin >> N >> K;

	if(N==2){
		if(K==3){
			printf("IMPOSSIBLE\n");
		} else {
			printf("POSSIBLE\n");
			if(K==2){
				printf("1 2\n2 1\n");
			} else {
				printf("2 1\n1 2\n");
			}
		}
		return;
	}

	int a=0, b=0, c=0;
	for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) for(int k=1; k<=N; k++){
		if((i==j)!=(i==k)) continue;
		if(i*(N-2)+j+k==K){
			a=i; b=j; c=k;
			epr("%i %i %i\n", i, j, k);
			if(solve1(i, j, k, N)) return;
		}
	}

	printf("IMPOSSIBLE\n");
	return;
}

int main(){
	int T;
	cin >> T;
	for(int t=1; t<=T; t++){
		printf("Case #%i: ", t);
		solve();
	}

	return 0;
}
