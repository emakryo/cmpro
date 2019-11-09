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

using lli = pair<pair<ll, ll>, int>;

int main(){
	int N, M;
	ll L;
	cin >> N >> M >> L;
	vector<vector<ll>> A(N, vector<ll>(N, 1e18));
	for(int i=0; i<M; i++){
		int a, b;
		ll c;
		cin >> a >> b >> c;
		a--; b--;
		A[a][b] = c;
		A[b][a] = c;
	}

	vector<vector<pair<ll, ll>>> dist(N, vector<pair<ll, ll>>(N, {1e18, -1e18}));

	for(int s=0; s<N; s++){
		priority_queue<lli, vector<lli>, greater<lli>> que;
		que.push({{0, -L}, s});
		dist[s][s] = {0, -L};
		while(!que.empty()){
			auto d = que.top().first;
			int v = que.top().second;
			que.pop();
			if(dist[s][v] < d) continue;
			for(int u=0; u<N; u++) if(u!=v&&A[u][v]<=L){
				auto dd = d;
				dd.second += A[u][v];
				if(dd.second>0){
					dd.first++;
					dd.second = -L+A[u][v];
				}
				debug(s, v, u, dd.first, dd.second);
				if(dd < dist[s][u]){
					dist[s][u] = dd;
					que.push({dd, u});
				}
			}
		}
	}

	int Q;
	cin >> Q;
	for(int i=0; i<Q; i++){
		int s, t;
		cin >> s >> t;
		s--; t--;
		if(dist[s][t] < pair<ll, ll>(1e18, -1e18)){
			cout << dist[s][t].first << endl;
		} else {
			cout << -1 << endl;
		}
	}

	return 0;
}
