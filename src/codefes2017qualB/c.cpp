#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

vector<vector<int>> graph;
vector<int> bipartite;
int dfs(int v, int p, int b){
	bipartite[v] = b;
	for(int u: graph[v]){
		if(u==p) continue;
		if(bipartite[u]==b) return -1;
		if(bipartite[u]==1-b) continue;
		if(dfs(u, v, 1-b)<0) return -1;
	}
	return 0;
}

int main(){
	int N, M;
	cin >> N >> M;
	graph.assign(N, {});
	for(int i=0; i<M; i++){
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	bipartite.assign(N, -1);
	if(dfs(0, -1, 0)<0){
		cout << (ll)N*(N-1)/2 - M << endl;
	} else {
		ll p = 0;
		for(int i=0; i<N; i++) p+=bipartite[i];
		cout << p*(N-p) - M << endl;
	}

	return 0;
}
