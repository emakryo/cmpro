#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(any{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

void dfs(int u, int c, int p, vector<vector<pair<int, int>>> &graph, vector<int> &color){
	int d = 1;
	debug(u, c, p);
	for(auto q: graph[u]){
		int v = q.first;
		int n = q.second;
		if(v==p) continue;
		if(d==c) d++;
		color[n] = d;
		dfs(v, d, u, graph, color);
		d++;
	}
}

int main(){
	int N;
	cin >> N;
	vector<vector<pair<int, int>>> graph(N);
	for(int i=0; i<N-1; i++){
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back({b, i});
		graph[b].push_back({a, i});
	}

	vector<int> color(N-1);
	dfs(0, 0, -1, graph, color);

	int k = 0;
	for(int i=0; i<N-1; i++){
		k = max(k, color[i]);
	}
	cout << k << endl;
	for(int i=0; i<N-1; i++){
		cout << color[i] << endl;
	}

	return 0;
}
