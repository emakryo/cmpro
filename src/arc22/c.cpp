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

vector<vector<int>> graph;
vector<int> depth;
void dfs(int u, int p){
	for(int v: graph[u]){
		if(v==p) continue;
		depth[v] = depth[u]+1;
		dfs(v, u);
	}
}

int main(){
	int N;
	cin >> N;
	graph.assign(N, {});
	for(int i=0; i<N-1; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	depth.assign(N, -1);

	depth[0] = 0;
	dfs(0, -1);
	int u = 0;
	for(int i=0; i<N; i++){
		if(depth[u]<depth[i]){
			u = i;
		}
	}
	depth.assign(N, -1);
	dfs(u, -1);
	int v = 0;
	for(int i=0; i<N; i++){
		if(depth[v]<depth[i]){
			v = i;
		}
	}

	cout << u+1 << " " << v+1 << endl;

	return 0;
}
