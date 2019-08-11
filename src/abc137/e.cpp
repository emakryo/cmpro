#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Mmax = 5000;
const ll INF = 1e9;
int N, M, P, A[Mmax], B[Mmax], C[Mmax];
vector<vector<int>> graph, rgraph;

void dfs(int v, vector<vector<int>> &graph, vector<bool> &reachable){
	for(int u: graph[v]){
		if(reachable[u]) continue;
		reachable[u] = true;
		dfs(u, graph, reachable);
	}
}

int main(){
	cin >> N >> M >> P;
	graph.resize(N);
	rgraph.resize(N);
	for(int i=0; i<M; i++){
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		A[i] = a;
		B[i] = b;
		C[i] = c;
		graph[a].push_back(b);
		rgraph[b].push_back(a);
	}

	vector<bool> r0(N), rN(N);
	r0[0] = true;
	rN[N-1] = true;
	dfs(0, graph, r0);
	dfs(N-1, rgraph, rN);

	vector<ll> d(N, INF);
	d[0] = 0;
	bool update = false;
	for(int i=0; i<=N; i++){
		update = false;
		for(int j=0; j<M; j++){
			if(r0[A[j]]&&r0[B[j]]&&rN[A[j]]&&rN[B[j]]&&d[A[j]]+P-C[j]<d[B[j]]){
				d[B[j]] = d[A[j]]+P-C[j];
				update = true;
			}
		}
		if(!update) break;
	}

	if(update){
		cout << -1 << endl;
	} else {
		cout << max(0ll, -d[N-1]) << endl;
	}

	return 0;
}
