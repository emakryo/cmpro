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
const int NMmax = 1e5;
const ll INF = 1e17;
int N,M,S,T;
int U[NMmax], V[NMmax];
ll A[NMmax], B[NMmax];

void dijkstra(vector<vector<pair<int, ll> > > &graph,
		int s, vector<ll> &cost){
	for(int i=0; i<N; i++) cost[i] = INF;
	priority_queue<pair<ll, int>, vector<pair<ll, int> >,
		greater<pair<ll, int> > > que;
	cost[s] = 0;
	que.push(make_pair(0, s));
	while(!que.empty()){
		ll c = que.top().first;
		int n = que.top().second;
		que.pop();
		if(c > cost[n]) continue;
		for(int i=0; i<graph[n].size(); i++){
			int m = graph[n][i].first;
			ll d = graph[n][i].second;
			if(cost[m] > c+d){
				cost[m] = c+d;
				que.push(make_pair(c+d, m));
			}
		}
	}
}


int main(){
	cin >> N >> M >> S >> T;
	S--; T--;
	for(int i=0; i<M; i++){
		cin >> U[i] >> V[i] >> A[i] >> B[i];
		U[i]--;
		V[i]--;
	}

	vector<vector<pair<int, ll> > > s_g(N), t_g(N);
	for(int i=0; i<M; i++){
		s_g[U[i]].push_back(make_pair(V[i], A[i]));
		s_g[V[i]].push_back(make_pair(U[i], A[i]));
		t_g[U[i]].push_back(make_pair(V[i], B[i]));
		t_g[V[i]].push_back(make_pair(U[i], B[i]));
	}

	vector<ll> s_cost(N), t_cost(N);
	dijkstra(s_g, S, s_cost);
	dijkstra(t_g, T, t_cost);
	//for(int i=0; i<N; i++){
	//	cout << s_cost[i] << " " << t_cost[i] << endl;
	//}

	vector<ll> ans(N);
	ans[N-1] = 1e15-s_cost[N-1]-t_cost[N-1];
	for(int i=N-2; i>=0; i--){
		ans[i] = max((ll)1e15-s_cost[i]-t_cost[i], ans[i+1]);
	}

	for(int i=0; i<N; i++){
		cout << ans[i] << endl;
	}

	return 0;
}
