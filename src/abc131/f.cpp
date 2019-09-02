#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

pair<ll, ll> dfs(int u, int b, vector<vector<int>> &graph, vector<bool> &visit){
	if(visit[u]) return {0, 0};
	visit[u] = true;
	pair<ll, ll> x = {0, 0};
	for(int v: graph[u]){
		auto p = dfs(v, 1-b, graph, visit);
		x.first += p.first;
		x.second += p.second;
	}
	if(b) x.second++;
	else x.first++;
	return x;
}

int main(){
	int N;
	cin >> N;
	vector<int> X(N), Y(N);
	for(int i=0; i<N; i++){
		cin >> X[i] >> Y[i];
		X[i]--; Y[i]--;
	}

	vector<vector<int>> graph(2e5);
	for(int i=0; i<N; i++){
		graph[X[i]].push_back(Y[i]+1e5);
		graph[Y[i]+1e5].push_back(X[i]);
	}

	vector<bool> visit(2e5);
	ll ans = 0;
	for(int i=0; i<1e5; i++){
		auto p = dfs(i, 0, graph, visit);
		ans += p.first * p.second;
	}
	cout << ans-N << endl;

	return 0;
}
