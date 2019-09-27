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
	vector<vector<pair<int, int>>> graph(N);
	for(int i=0; i<M; i++){
		int a, b, c;
		cin >> c >> a >> b;
		graph[a].push_back({b, c});
		graph[b].push_back({a, c});
	}

	vector<map<int, ll>> dist(N);
	vector<pair<int, ll>> mdist(N, {1e9, 1e18});
	typedef pair<ll, pair<int, int>> qitem;
	priority_queue<qitem, vector<qitem>, greater<qitem>> que;
	que.push({0, {0, 0}});
	while(!que.empty()){
		qitem x = que.top();
		que.pop();
		ll d = x.first;
		int v = x.second.first;
		int b = x.second.second;
		debug(d, v, b, mdist[v].first, mdist[v].second);

		if(mdist[v].first<b&&mdist[v].second<d) continue;
		if(dist[v].count(b)>0&&dist[v][b]<=d) continue;
		dist[v][b] = d;
		if(d < mdist[v].second){
			mdist[v] = {b, d};
		}
		for(auto p: graph[v]){
			int u = p.first;
			int c = p.second;
			if(c==0){
				int dn = d+1;
				if(dist[u].count(b)==0||dn<dist[u][b]){
					que.push({dn, {u, b}});
				}
			} else {
				int dn = d+b+1;
				if(dist[u].count(b+1)==0||dn<dist[u][b+1]){
					que.push({dn, {u, b+1}});
				}
			}
		}
	}

	for(int i=0; i<N; i++){
		cout << mdist[i].second << endl;
	}

	return 0;
}
