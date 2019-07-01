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
const int Mmax = 1e5;
const int INF = 1e9;
int N, M, U[Mmax], V[Mmax], S, T;


int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++){
		cin >> U[i] >> V[i];
		U[i]--;
		V[i]--;
	}
	cin >> S >> T;
	S--;
	T--;

	vector<vector<int> > graph(N);
	for(int i=0; i<M; i++){
		graph[U[i]].push_back(V[i]);
	}

	vector<vector<int>> dist(N, vector<int>(3, INF));
	dist[S] = {0, INF, INF};
	queue<pair<int, int> > que;
	que.push({S, 0});
	while(!que.empty()){
		int u = que.front().first;
		int r = que.front().second;
		//cout << u+1 << " " << r << endl;
		que.pop();
		for(int v: graph[u]){
			if(dist[u][r] + 1 < dist[v][(r+1)%3]){
				dist[v][(r+1)%3] = dist[u][r]+1;
				que.push({v, (r+1)%3});
			}
		}
	}

	if(dist[T][0] < INF){
		cout << dist[T][0] / 3 << endl;
	} else {
		cout << -1 << endl;
	}

	return 0;
}
