#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
ostream& operator<<(ostream &os, vector<T> &v){
	string sep = " ";
	if(v.size()) os << v[0];
	for(int i=1; i<v.size(); i++) os << sep << v[i];
	return os;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
	cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__);
#else
#define dbg(...) 
#endif

int main() {
	ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> graph(n);
	for(int i=0; i<m; i++){
		int u, v;
		cin >> u >> v;
		u--; v--;
		graph[v].push_back(u);
		graph[u].push_back(v);
	}

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;
	que.push({0, 0});
	vector<int> dist(n, 1e9);
	while(!que.empty()){
		int d = que.top().first;
		int u = que.top().second;
		que.pop();
		if(d>=dist[u]) continue;
		dist[u] = d;

		for(int v: graph[u]){
			int nd = d+1;
			que.push({nd, v});
		}
	}

	cout << "Yes" << endl;
	for(int i=1; i<n; i++){
		int ans = -1;
		for(int v: graph[i]){
			if(dist[v]+1==dist[i]){
				ans = v;
			}
		}
		cout << ans+1 << endl;
	}

	return 0;
}
