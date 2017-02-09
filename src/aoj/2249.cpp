//#include<iostream>
//#include<iomanip>
#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 10000;
const int Mmax = 20000;
int N, M;
int U[Mmax], V[Mmax], D[Mmax], C[Mmax];

struct edge {
	int to, cost, dist;
};

int main(){
	while(true){
		scanf("%d%d", &N, &M);
		if(N == 0 && M==0) break;
		edge e;
		vector<vector<edge> > graph(N);
		for(int i=0; i<M; i++){
			scanf("%d%d%d%d", &U[i], &V[i], &D[i], &C[i]);
			U[i]--;
			V[i]--;
			e.to = V[i];
			e.cost = C[i];
			e.dist = D[i];
			graph[U[i]].push_back(e);
			e.to = U[i];
			graph[V[i]].push_back(e);
		}

		priority_queue<pair<int, int>, vector<pair<int, int> >, less<pair<int, int> > > que;
		vector<int> dist(N, 1e8);
		dist[0] = 0;
		que.push(make_pair(0, 0));
		while(!que.empty()){
			int d = que.top().first;
			int n = que.top().second;
			que.pop();
			if(dist[n] < d) continue;

			for(int i=0; i<graph[n].size(); i++){
				int m = graph[n][i].to;
				if(dist[m] > dist[n]+graph[n][i].dist){
					dist[m] = dist[n]+graph[n][i].dist;
					que.push(make_pair(dist[m], m));
				}
			}
		}

		//for(int i=0; i<N; i++) printf("%d ", dist[i]);
		//puts("");

		vector<pair<int, int> > dn;
		for(int i=0; i<N; i++) dn.push_back(make_pair(dist[i],i));
		sort(dn.begin(), dn.end());

		vector<bool> done(N, false);
		done[0] = true;
		int ans = 0;
		for(int i=0; i<N; i++){
			int n = dn[i].second;
			if(n == 0) continue;
			int tmp = 1e8;
			for(int j=0; j<graph[n].size(); j++){
				int m = graph[n][j].to;
				if(dist[n] == graph[n][j].dist + dist[m] && done[m]){
					tmp = min(tmp, graph[n][j].cost);
				}
			}
			ans += tmp;
			done[n] = true;
		}

		printf("%d\n", ans);
	}

	return 0;
}
