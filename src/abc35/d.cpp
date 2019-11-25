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
	ll T;
	cin >> N >> M >> T;
	vector<int> A(N);
	for(int i=0; i<N; i++) cin >> A[i];
	vector<vector<pair<int, ll>>> graph(N);
	vector<vector<pair<int, ll>>> rgraph(N);
	for(int i=0; i<M; i++){
		int a, b;
		ll c;
		cin >> a >> b >> c;
		a--; b--;
		graph[a].push_back({b, c});
		rgraph[b].push_back({a, c});
	}

	vector<ll> dist1(N, 1e15);
	dist1[0] = 0;
	using pli = pair<ll, int>;
	priority_queue<pli, vector<pli>, greater<pli>> que;
	que.push({0, 0});
	while(!que.empty()){
		pli p = que.top();
		que.pop();
		int u = p.second;
		ll d = p.first;
		if(dist1[u]<d) continue;
		for(int i=0; i<graph[u].size(); i++){
			int v = graph[u][i].first;
			ll c = graph[u][i].second;
			if(dist1[u]+c < dist1[v]){
				dist1[v] = dist1[u]+c;
				que.push({dist1[v], v});
			}
		}
	}

	vector<ll> dist2(N, 1e15);
	dist2[0] = 0;
	que.push({0, 0});
	while(!que.empty()){
		pli p = que.top();
		que.pop();
		int u = p.second;
		ll d = p.first;
		if(dist2[u]<d) continue;
		for(int i=0; i<rgraph[u].size(); i++){
			int v = rgraph[u][i].first;
			ll c = rgraph[u][i].second;
			if(dist2[u]+c < dist2[v]){
				dist2[v] = dist2[u]+c;
				que.push({dist2[v], v});
			}
		}
	}

	ll ans = 0;
	for(int u=0; u<N; u++){
		if(dist1[u]+dist2[u]<T){
			ans = max((T-dist1[u]-dist2[u])*A[u], ans);
		}
	}
	cout << ans << endl;

	return 0;
}
