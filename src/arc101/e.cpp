#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Nmax = 5000;
const ll P = 1e9+7;
int N, X[Nmax], Y[Nmax];
vector<vector<int>> graph;
vector<int> nchild;
vector<vector<pair<ll, ll>>> dp;
vector<ll> n_pair;

int dfs_nchild(int v, int p){
	int ret = 1;
	for(int u: graph[v]){
		if(u==p) continue;
		ret += dfs_nchild(u, v);
	}
	nchild[v] = ret;
	return ret;
}

void dfs(int v, int p){
	dp[v][0] = {1, 0};
	int n = 1;
	for(int u: graph[v]){
		if(u==p) continue;
		dfs(u, v);
		vector<pair<ll, ll>> tmp(N);
		for(int x=0; x<n; x++){
			for(int y=0; y<nchild[u]; y++){
				tmp[x+y+1].first += dp[v][x].first * dp[u][y].first;
				tmp[x+y+1].first += dp[v][x].second * dp[u][y].second;
				tmp[x+y+1].first %= P;
				tmp[x+y+1].second += dp[v][x].first * dp[u][y].second;
				tmp[x+y+1].second += dp[v][x].second * dp[u][y].first;
				tmp[x+y+1].second %= P;
				tmp[x].first += dp[v][x].first * dp[u][y].second % P * n_pair[y+1];
				tmp[x].first += dp[v][x].second * dp[u][y].first % P * n_pair[y+1];
				tmp[x].first %= P;
				tmp[x].second += dp[v][x].first * dp[u][y].first % P * n_pair[y+1];
				tmp[x].second += dp[v][x].second * dp[u][y].second % P * n_pair[y+1];
				tmp[x].second %= P;
			}
		}
		n += nchild[u];
		dp[v] = tmp;
		//cout << v <<" "<<u<< endl;
		//for(int x=0; x<nchild[v]; x++) cout << dp[v][x].first << " ";
		//cout << endl;
		//for(int x=0; x<nchild[v]; x++) cout << dp[v][x].second << " ";
		//cout << endl;
	}
}



int main(){
	cin >> N;
	for(int i=0; i<N-1; i++){
		cin >> X[i] >> Y[i];
		X[i]--; Y[i]--;
	}
	graph.resize(N);
	for(int i=0; i<N-1; i++){
		graph[X[i]].push_back(Y[i]);
		graph[Y[i]].push_back(X[i]);
	}

	nchild.resize(N);
	dfs_nchild(0, -1);
	n_pair.resize(N+1);
	n_pair[0] = 1;
	for(int i=2; i<=N; i++){
		n_pair[i] = (i-1)*n_pair[i-2]%P;
	}

	dp.resize(N, vector<pair<ll, ll>>(N));
	dfs(0, -1);

	ll ans = 0;
	for(int x=0; x<N; x++){
		ans -= dp[0][x].second * n_pair[x+1];
		ans += dp[0][x].first * n_pair[x+1];
		ans += P;
		ans %= P;
	}
	cout << ans << endl;

	return 0;
}
