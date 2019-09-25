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

int N, M;
vector<vector<int>> graph;
ll dfs(int u, int s){
	debug(any{u, s});
	s += 1<<u;
	if(s == (1<<N)-1) return 1;
	int r = 0;
	for(int v: graph[u]){
		if((s>>v)&1) continue;
		r += dfs(v, s);
	}
	return r;
}

int main(){
	cin >> N >> M;
	graph.assign(N, {});
	for(int i=0; i<M; i++){
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	cout << dfs(0, 0) << endl;;

	return 0;
}
