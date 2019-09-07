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

const ll P = 1e9+7;
int N, K;
ll dfs(int u, int p, vector<vector<int>> &graph){
	int i=p<0?(K-1):(K-2);
	ll ret = 1;
	for(int v: graph[u]){
		if(v==p) continue;
		ret *= (dfs(v, u, graph) * i--) % P;
		ret %= P;
	}
	debug(any{u+1, ret});
	return ret;
}

int main(){
	cin >> N >> K;
	vector<int> A(N-1), B(N-1);
	vector<vector<int>> graph(N);
	for(int i=0; i<N-1; i++){
		cin >> A[i] >> B[i];
		graph[A[i]-1].push_back(B[i]-1);
		graph[B[i]-1].push_back(A[i]-1);
	}

	cout << K * dfs(0, -1, graph) % P << endl;

	return 0;
}
