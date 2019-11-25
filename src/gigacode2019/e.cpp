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
const double INF = 1e18;

int main(){
	int N;
	ll L;
	cin >> N >> L;
	vector<ll> X(N+2), V(N+2), D(N+2);
	X[0] = 0;
	cin >> V[0] >> D[0];
	for(int i=1; i<=N; i++){
		cin >> X[i] >> V[i] >> D[i];
	}
	X[N+1] = L;

	vector<pair<ll, int>> xi(N+2);
	for(int i=0; i<N+2; i++) xi[i] = {X[i], i};
	sort(xi.begin(), xi.end());

	vector<vector<pair<int, double>>> graph(N+2);
	for(int i=0; i<N+2; i++){
		int k = xi[i].second;
		for(int j=i+1; j<N+2; j++){
			int l = xi[j].second;
			if(X[l]-X[k]>D[k]) break;
			graph[k].push_back({l, (double)(X[l]-X[k])/V[k]});
		}
	}

	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> que;
	vector<double> dist(N+2, INF);
	que.push({0, 0});
	dist[0] = 0;

	while(!que.empty()){
		auto p = que.top();
		que.pop();
		int v = p.second;
		double d = p.first;
		if(d < dist[v]) continue;
		for(auto q: graph[v]){
			int u = q.first;
			double c = q.second;
			if(dist[v]+c<dist[u]){
				dist[u] = dist[v]+c;
				que.push({dist[u], u});
			}
		}
	}

	if(dist[N+1] == INF){
		cout << "impossible" << endl;
	} else {
		cout << setprecision(20) << fixed << dist[N+1] << endl;
	}

	return 0;
}
