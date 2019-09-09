#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

vector<ll> ans;
vector<vector<int>> graph;
vector<ll> sum;
void dfs(int v, int p, ll s){
	ans[v] = s + sum[v];
	for(int u: graph[v]){
		if(u==p) continue;
		dfs(u, v, ans[v]);
	}
}

int main(){
	int N, Q;
	cin >> N >> Q;
	vector<int> A(N), B(N);
	for(int i=0; i<N-1; i++) cin >> A[i] >> B[i];
	vector<int> P(Q), X(Q);
	for(int i=0; i<Q; i++) cin >> P[i] >> X[i];

	graph.assign(N, {});
	for(int i=0; i<N-1; i++){
		A[i]--; B[i]--;
		graph[A[i]].push_back(B[i]);
		graph[B[i]].push_back(A[i]);
	}
	sum.assign(N, 0);
	for(int i=0; i<Q; i++){
		P[i]--;
		sum[P[i]] += X[i];
	}

	ans.assign(N, 0);
	dfs(0, -1, 0);
	pr(ans);
	return 0;
}
