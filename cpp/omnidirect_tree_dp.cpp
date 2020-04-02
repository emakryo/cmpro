#include<bits/stdc++.h>
using namespace std;

struct Elem {
	Elem() {}
	Elem& operator+=(Elem &c) {
		return *this;
	}
	Elem add_self() const {
		Elem ret(*this);
		return ret;
	}
	Elem operator-(Elem &o) const {
		Elem ret(*this);
		return ret;
	}
};

Elem dp[20005];
vector<vector<int>> graph;

void dfs(int u, int p){
	for(int v: graph[u]) {
		if(v==p) continue;
		dfs(v, u);
		dp[u] += dp[v];
	}
	dp[u] = dp[u].add_self();
}

void omnidirect(int u, int p){
	Elem sum;
	for(int v: graph[u]){
		sum += dp[v];
	}
	for(int v: graph[u]){
		if(v==p) continue;
		dp[u] = (sum - dp[v]).add_self();
		omnidirect(v, u);
	}
	dp[u] = sum.add_self();
}

int main() {
	dfs(0, -1);
	omnidirect(0, -1);
}
