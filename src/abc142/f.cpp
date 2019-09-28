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

int dfs(int u, vector<int> &path, vector<bool> &visit){
	visit[u] = true;
	for(int v: graph[u]){
		path[u] = v;
		if(path[v]>=0) return v;
		if(visit[v]) continue;
		int c = dfs(v, path, visit);
		if(c >= 0) return c;
	}
	path[u] = -1;
	return -1;
}

int main(){
	int N, M; cin >> N >> M;
	graph.assign(N, {});
	for(int i=0; i<M; i++){
		int a, b; cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
	}

	vector<int> path;
	int first = -1;
	for(int i=0; i<N; i++){
		vector<bool> visit(N);
		path.assign(N, -1);
		first = dfs(i, path, visit);
		if(first >= 0) break;
	}
	if(first<0) {
		cout << -1 << endl;
		return 0;
	}

	vector<bool> loop(N);
	int next = first;
	while(!loop[next]){
		debug("a", next, path[next]);
		loop[next] = true;
		next = path[next];
	}
	while(true){
		bool update = false;
		int u = first;
		int t = -1;
		//debug("pohe");
		while(true){
			debug("b", u, path[u], first);
			for(int v: graph[u]){
				if(!loop[v]) continue;
				if(v == path[u]) continue;
				t = v;
				break;
			}
			if(t >= 0){
				debug(u, t, path[u]);
				path[u] = t;
				update = true;
				break;
			}
			u = path[u];
			if(u==first) break;
		}
		if(update){
			loop.assign(N, false);
			int v = u;
			first = u;
			while(true){
				//debug(v, path[v]);
				loop[v] = true;
				v = path[v];
				if(v == u) break;
			}
		} else {
			break;
		}
	}

	vector<int> ans;
	for(int i=0; i<N; i++){
		if(loop[i]) ans.push_back(i);
	}
	cout << ans.size() << endl;
	for(int a: ans){
		cout << a+1 << endl;
	}

	return 0;
}
