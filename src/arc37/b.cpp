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
int N, M;
vector<vector<int> > graph;

int dfs(vector<int> &visit, int n, int p){
	visit[n] = 1;
	int ret = 0;
	for(int i=0; i<graph[n].size(); i++){
		int m = graph[n][i];
		if(m == p) continue;
		if(visit[m] > 0) return 0;
		if(dfs(visit, m, n) == 0) return 0;
	}
	return 1;
}

int main(){
	cin >> N >> M;
	graph = vector<vector<int> >(N);
	for(int i=0; i<M; i++){
		int u, v;
		cin >> u >> v;
		u--; v--;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	vector<int> visit(N);
	int ans = 0;
	for(int i=0; i<N; i++){
		if(visit[i]>0) continue;
		ans += dfs(visit, i, -1);
	}
	cout << ans << endl;

	return 0;
}
