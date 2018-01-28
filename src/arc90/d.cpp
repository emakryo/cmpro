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
const ll INF = 1e15;
const int Nmax = 1000000;
const int Mmax = 2000000;
ll L[Mmax], R[Mmax], D[Mmax], N, M;

ll dfs(int v, vector<vector<pair<int, ll> > > &graph, vector<ll> &position){
	for(int i=0; i<graph[v].size(); i++){
		int u = graph[v][i].first;
		ll d = graph[v][i].second;
		if(position[u] == -INF){
			position[u] = position[v]+d;
			//cout << u << " " << position[u] << endl;
			ll diff = dfs(u, graph, position);
			if(diff != 0){
				position[u] = -INF;
				return diff;
			}
		}
		else if(position[u] != position[v]+d){
			return position[v]+d-position[u];
		}
	}
	return 0;
}

int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++){
		cin >> L[i] >> R[i] >> D[i];
		L[i]--; R[i]--;
	}

	vector<vector<pair<int, ll> > > graph(N);
	for(int i=0; i<M; i++){
		graph[L[i]].push_back(make_pair(R[i], D[i]));
		graph[R[i]].push_back(make_pair(L[i], -D[i]));
	}

	vector<ll> position(N, -INF);
	for(int i=0; i<N; i++){
		if(position[i] > -INF) continue;
		position[i] = 0;
		ll diff = dfs(i, graph, position);
		//cout << diff << endl;
		if(diff != 0){
			position[i] = -diff;
			diff = dfs(i, graph, position);
			//cout << " " << diff << endl;
			if(diff != 0){
				cout << "No" << endl;
				return 0;
			}
		}
	}

	cout << "Yes" << endl;

	return 0;
}
