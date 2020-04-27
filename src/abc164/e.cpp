#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> anys;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(anys{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

int main(){
	int N, M;
	ll S;
	cin >> N >> M >> S;
	vector<int> U(M), V(M), A(M), B(M);
	for(int i=0; i<M; i++){
		int u, v;
		ll a, b;
		cin >> u >> v >> a >> b;
		u--; v--;
		U[i] = u;
		V[i] = v;
		A[i] = a;
		B[i] = b;
	}
	vector<ll> C(N), D(N);
	for(int i=0; i<N; i++){
		cin >> C[i] >> D[i];
	}

	ll Xmax = 5010;
	vector<vector<pair<int, ll>>> graph(N*Xmax);
	for(int i=0; i<N; i++){
		for(int x=0; x<Xmax; x++){
			if(x>0) graph[i+x*N].push_back({i+(x-1)*N, 0});
			graph[i+x*N].push_back({i+min(Xmax-1, (x+C[i]))*N, D[i]});
		}
	}

	for(int i=0; i<M; i++){
		for(int x=0; x<Xmax; x++){
			if(x-A[i]>=0){
				graph[U[i]+x*N].push_back({V[i]+(x-A[i])*N, B[i]});
				graph[V[i]+x*N].push_back({U[i]+(x-A[i])*N, B[i]});
			}
		}
	}

	vector<ll> dist(N*Xmax, 1e18);
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> que;
	int s = min(S, Xmax-1)*N;
	dist[s] = 0;
	que.push({0, s});
	while(!que.empty()){
		auto p=que.top();
		int u = p.second;
		ll d = p.first;
		que.pop();
		if(dist[u] < d) continue;
		for(auto q: graph[u]){
			if(dist[u]+q.second<dist[q.first]){
				dist[q.first] = dist[u]+q.second;
				que.push({dist[q.first], q.first});
			}
		}
	}

	for(int i=1; i<N; i++){
		ll ans = 1e18;
		for(int x=0; x<Xmax; x++){
			ans=min(ans, dist[i+x*N]);
			if(x<10) debug(i, x, dist[i+x*N]);
		}
		cout << ans << endl;
	}

	return 0;
}
