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

void dfs(int u, int p, vector<vector<int>> &graph, vector<int> &depth){
	for(int v: graph[u]){
		if(v == p) continue;
		depth[v] = depth[u]+1;
		dfs(v, u, graph, depth);
	}
}

int main(){
	int N;
	cin >> N;
	vector<vector<int>> graph(N);
	for(int i=0; i<N-1; i++){
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	vector<int> depth(N);
	depth[0] = 1;
	dfs(0, -1, graph, depth);

	int mx = depth[0], u = 0;
	for(int i=0; i<N; i++){
		if(depth[i]>mx){
			mx = depth[i];
			u = i;
		}
	}

	depth.assign(N, 0);
	depth[u] = 1;
	dfs(u, -1, graph, depth);

	mx = depth[0];
	for(int i=0; i<N; i++) mx = max(depth[i], mx);
	debug(mx);

	if(mx%3 == 2) {
		cout << "Second" << endl;
	} else {
		cout << "First" << endl;
	}

	return 0;
}
