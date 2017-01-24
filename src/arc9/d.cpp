#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Amax = 100;
const int Nmax = 10;
const int Mmax = 10000;
const int Tmax = 1000;
int A, T, K, N[Amax], C[Amax][Nmax];
int M, E1[Mmax], E2[Mmax], D[Mmax];
bool town[Amax][Tmax];
vector<int> edge[Amax];
vector<int> par(Tmax);
ll dp[77*77*7];

int root(int x){
	if(x == par[x]) return x;
	return par[x] = root(par[x]);
}

void unite(int x, int y){
	int rx = root(x);
	int ry = root(y);
	if(rx == ry) return;
	par[rx] = ry;
}

void dfs(int a, int n, vector<int> &edges, map<int, ll> &cost){
	if(edges.size() == N[a]-1){
		int c = 0;
		for(int i=0; i<edges.size(); i++){
			c += D[edges[i]];
		}
		for(int i=0; i<edges.size(); i++){
			unite(E1[edges[i]], E2[edges[i]]);
		}
		bool connected = true;
		for(int i=0; i<N[a]; i++){
			par[C[a][i]] = root(C[a][i]);
			if(par[C[a][0]] != par[C[a][i]]) connected = false;
		}
		if(connected){
			cost[c] += 1;
		}
		for(int i=0; i<N[a]; i++){
			par[C[a][i]] = C[a][i];
		}
		return;
	}

	if(edges.size() + edge[a].size() - n < N[a] - 1) return;

	for(int i=n; i<edge[a].size(); i++){
		edges.push_back(edge[a][i]);
		dfs(a, i+1, edges, cost);
		edges.pop_back();
	}
}

int main(){
	cin >> A >> T >> K;
	for(int i=0; i<A; i++){
		cin >> N[i];
		for(int j=0; j<N[i]; j++){
			cin >> C[i][j];
			C[i][j]--;
		}
	}
	cin >> M;
	int total = 0;
	for(int i=0; i<M; i++){
		cin >> E1[i] >> E2[i] >> D[i];
		E1[i]--;
		E2[i]--;
		total += D[i];
	}

	for(int i=0; i<T; i++) par[i] = i;

	dp[0] = 1;
	for(int i=0; i<A; i++){
		for(int j=0; j<N[i]; j++){
			town[i][C[i][j]] = true;
		}
		for(int j=0; j<M; j++){
			if(town[i][E1[j]] && town[i][E2[j]]){
				edge[i].push_back(j);
			}
		}
		vector<int> list;
		map<int, ll> cost;
		dfs(i, 0, list, cost);
		/*
		for(map<int, ll>::iterator k=cost[i].begin(); k!=cost[i].end(); k++){
			cout << k->first << " " << k->second << endl;
		}
		*/
		for(int j=77*77*7; j>=0; j--){
			if(dp[j] == 0) continue;
			for(map<int, ll>::iterator k=cost.begin(); k!=cost.end(); k++){
				if(dp[j] >= 1e8 || dp[j]*k->second >= 1e8){
					dp[j+k->first] = 1e8;
				}
				else{
					dp[j+k->first] += dp[j]*k->second;
				}
			}
			dp[j] = 0;
		}
	}

	ll k = 0;
	for(int i=77*77*7; i>=0; i--){
		//cout << i << " " << dp[(A-1)%2][i] << endl;
		k += dp[i];
		if(k >= K){
			cout << total - i << endl;
			break;
		}
	}
	if(k < K){
		cout << -1 << endl;
	}

	return 0;
}
