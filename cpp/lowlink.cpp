#include<bits/stdc++.h>
using namespace std;

struct LowLink {
	int n;
	vector<vector<int>> graph;
	vector<int> used, ord, low;
	vector<bool> articulation;
	set<pair<int, int>> bridge;

	LowLink(int n): n(n) {
		graph.assign(n, {});
	}
	void add_edge(int u, int v){
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	int dfs(int u, int p, int k) {
		used[u] = true;
		ord[u] = k++;
		low[u] = ord[u];
		int cnt = 0;
		for(int v : graph[u]) {
			if(!used[v]) {
				++cnt;
				k = dfs(v, u, k);
				low[u] = min(low[u], low[v]);
				articulation[u] = articulation[u] ||(~p && low[v] >= ord[u]);
				if(ord[u] < low[v]) bridge.insert(minmax(u, v));
			} else if(v != p) {
				low[u] = min(low[u], ord[v]);
			}
		}
		articulation[u] = articulation[u] || (p == -1 && cnt > 1);
		return k;
	}
	void build() {
		used.assign(n, 0);
		ord.assign(n, 0);
		low.assign(n, 0);
		articulation.assign(n, false);
		int k = 0;
		for(int i = 0; i < n; i++) {
			if(!used[i]) k = dfs(i, -1, k);
		}
	}
};
