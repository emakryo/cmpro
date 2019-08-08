#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N, X;
vector<vector<pair<int, int>>> graph;
vector<int> sum;

void dfs(int u, int p, int z){
	for(auto pa: graph[u]){
		int v = pa.first;
		int c = pa.second;
		if(v==p) continue;
		dfs(v, u, z^c);
		sum[v] = z^c;
	}
}

int main(){
	cin >> N >> X;
	graph = vector<vector<pair<int, int>>>(N);
	for(int i=0; i<N-1; i++){
		int u, v, c;
		cin >> u >> v >> c;
		u--; v--;
		graph[u].push_back({v, c});
		graph[v].push_back({u, c});
	}

	sum = vector<int>(N);
	dfs(0, -1, 0);

	ll ans = 0;
	set<int> done;
	map<int, ll> m;
	for(int i=0; i<N; i++){
		//cout << i<< " " <<sum[i] << endl;
		m[sum[i]]++;
	}
	for(auto xs: m){
		int x = xs.first;
		ll n = xs.second;
		if(X==0){
			ans += n*(n-1)/2;
		} else {
			auto ys = m.find(x^X);
			if(ys != m.end() && done.find(x^X) == done.end()){
				ans += n*ys->second;
			}
		}
		done.insert(x);
	}
	cout << ans << endl;
	return 0;
}
