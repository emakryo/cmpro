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

int main(){
	int N, M;
	cin >> N >> M;
	vector<int> L(M), R(M);
	vector<ll> C(M);
	vector<vector<int>> ls(N), rs(N);
	for(int i=0; i<M; i++){
		cin >> L[i] >> R[i] >> C[i];
		L[i]--; R[i]--;
		ls[L[i]].push_back(i);
		rs[R[i]].push_back(i);
	}

	vector<vector<pair<int, ll>>> graph(2*M+N);
	for(int i=0; i<M; i++){
		graph[i].push_back({i+M, C[i]});
		graph[i].push_back({2*M+L[i], 0});
		graph[2*M+L[i]].push_back({i, 0});
		graph[i+M].push_back({2*M+R[i], 0});
		graph[2*M+R[i]].push_back({i+M, 0});
	}
	for(int i=0; i<N-1; i++){
		graph[2*M+i+1].push_back({2*M+i, 0});
	}

	for(int i=0; i<2*M+N; i++){
		for(auto p: graph[i]){
			debug(i, p.first, p.second);
		}
	}

	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> que;
	que.push({0, 2*M});
	vector<ll> dist(2*M+N, 1e16);
	dist[2*M] = 0;
	while(!que.empty()){
		auto p = que.top();
		que.pop();
		ll d = p.first;
		int u = p.second;
		if(dist[u]<d) continue;
		dist[u] = d;
		for(auto q: graph[u]){
			ll v = q.first;
			ll c = q.second;
			if(dist[v]>dist[u]+c){
				dist[v] = dist[u]+c;
				que.push({dist[v], v});
				//debug(u, d);
			}
		}
	}

	if(dist[2*M+N-1] < 1e16){
		cout << dist[2*M+N-1] << endl;
	} else {
		cout << -1 << endl;
	}

	return 0;
}
