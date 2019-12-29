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

void dfs(int u, int p, int d, vector<int> &depth, vector<int> &sub_max, vector<vector<int>> &graph){
	depth[u] = d;
	int s = 0;
	for(int v: graph[u]){
		if(v==p) continue;
		dfs(v, u, d+1, depth, sub_max, graph);
		s = max(sub_max[v]+1, s);
	}
	sub_max[u] = s;
}

int main(){
	int N, U, V;
	cin >> N >> U >> V;
	U--; V--;
	vector<vector<int>> graph(N);
	for(int i=0; i<N-1; i++){
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	vector<int> depth(N), sub_max(N);
	dfs(V, -1, 0, depth, sub_max, graph);

	int ans = 0;
	int x = U;
	while(x != V) {
		int a = depth[x];
		int b = depth[U]-depth[x];
		if(a <= b) break;
		ans = max(ans, b + sub_max[x] + a - b - 1);

		for(int y: graph[x]){
			if(depth[x]==depth[y]+1){
				x = y;
				break;
			}
		}
	}
	cout << ans << endl;

	return 0;
}
