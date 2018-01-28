#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const ll INF = 1e17;
const ll P = 1e9+7;
const int Mmax = 2000000;
int N, M, S, T;
int U[Mmax], V[Mmax];
ll D[Mmax];

int main(){
	cin >> N >> M;
	cin >> S >> T;
	S--; T--;
	for(int i=0; i<M; i++){
		cin >> U[i] >> V[i] >> D[i];
		U[i]--;
		V[i]--;
	}

	vector<vector<pair<int, ll> > > graph(N);
	for(int i=0; i<M; i++){
		graph[U[i]].push_back(make_pair(V[i], D[i]));
		graph[V[i]].push_back(make_pair(U[i], D[i]));
	}

	vector<ll> dist(N, INF);
	priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > que;
	que.push(make_pair(0, S));
	dist[S] = 0;
	while(!que.empty()){
		ll d = que.top().first;
		int v = que.top().second;
		que.pop();
		for(int i=0; i<graph[v].size(); i++){
			int u = graph[v][i].first;
			int du = graph[v][i].second;
			if(d + du < dist[u]){
				dist[u] = d+du;
				que.push(make_pair(dist[u], u));
			}
		}
	}

	vector<pair<ll, int> > vec(N);
	for(int i=0; i<N; i++){
		vec[i] = make_pair(dist[i], i);
	}
	sort(vec.begin(), vec.end());

	vector<ll> dps(N);
	dps[S] = 1;
	for(int i=0; i<N; i++){
		int v = vec[i].second;
		for(int j=0; j<graph[v].size(); j++){
			int u = graph[v][j].first;
			ll du = graph[v][j].second;
			if(dist[u] != dist[v]+du) continue;
			dps[u] = (dps[u]+dps[v])%P;
		}
	}

	vector<ll> dpt(N);
	dpt[T] = 1;
	for(int i=0; i<N; i++){
		int v = vec[N-i-1].second;
		for(int j=0; j<graph[v].size(); j++){
			int u = graph[v][j].first;
			ll du = graph[v][j].second;
			if(dist[u]+du != dist[v]) continue;
			dpt[u] = (dpt[u]+dpt[v])%P;
		}
	}

	ll exclude = 0;
	for(int i=0; i<N; i++){
		int v = vec[i].second;
		if(2*dist[v] == dist[T]){
			//cout << v << endl;
			exclude += ((dps[v]*dps[v])%P)*((dpt[v]*dpt[v])%P);
			exclude %= P;
		}
		for(int j=0; j<graph[v].size(); j++){
			int u = graph[v][j].first;
			ll du = graph[v][j].second;
			if(dist[u] != dist[v]+du) continue;
			if(2*dist[u] > dist[T] && dist[T] > 2*dist[v]){
				//cout << v << " " << u << endl;
				//cout << dps[v] << " " << dpt[u] << endl;
				exclude += ((dps[v]*dps[v])%P)*((dpt[u]*dpt[u])%P);
				exclude %= P;
			}
		}
	}

	//cout << dps[T] << endl;
	cout << ((dps[T]*dps[T])%P - exclude + P)%P << endl;

	return 0;
}
