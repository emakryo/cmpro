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
const int Nmax = 2000;
int N, K;
vector<vector<int>> graph;

int dfs(int v, int p, int r){
	if(r==0) return 1;
	int s = 1;
	for(int u: graph[v]){
		if(u==p) continue;
		s += dfs(u, v, r-1);
	}
	return s;
}

int main(){
	cin >> N >> K;
	graph = vector<vector<int>>(N);
	for(int i=0; i<N-1; i++){
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	int within_rad = 0;
	if(K%2){
		for(int u=0; u<N; u++){
			for(int v: graph[u]){
				within_rad = max(within_rad, dfs(u, v, K/2)+dfs(v, u, K/2));
			}
		}
	} else {
		for(int i=0; i<N; i++){
			within_rad = max(within_rad, dfs(i, -1, K/2));
		}
	}

	cout << max(0, N-within_rad) << endl;

	return 0;
}
