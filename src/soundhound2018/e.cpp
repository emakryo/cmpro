#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
#include<set>
using namespace std;
typedef long long ll;
const int NMmax = 1e5;
const ll INF = 1e17;
int N, M;
int U[NMmax], V[NMmax];
ll S[NMmax];

void dfs(int v, vector<ll> &x, vector<bool> &z, vector<vector<pair<int, ll> > > &g){
	for(int i=0; i<g[v].size(); i++){
		int u = g[v][i].first;
		ll s = g[v][i].second;
		if(x[u]==INF){
			x[u] = s-x[v];
			z[u] = !z[v];
			dfs(u, x, z, g);
		}
	}
}

void f(ll x0, vector<ll> &x, vector<bool> &z, vector<vector<pair<int, ll> > > &g){
	x = vector<ll>(N, INF);
	z = vector<bool>(N);
	x[0] = x0;
	dfs(0, x, z, g);
}

int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++){
		cin >> U[i] >> V[i] >> S[i];
		U[i]--; V[i]--;
	}

	vector<vector<pair<int, ll> > > graph(N);
	for(int i=0; i<M; i++){
		graph[U[i]].push_back(make_pair(V[i], S[i]));
		graph[V[i]].push_back(make_pair(U[i], S[i]));
	}

	vector<ll> x;
	vector<bool> z;
	set<ll> s;
	f(0, x, z, graph);
	for(int i=0; i<M; i++){
		if(z[U[i]]==z[V[i]]){
			ll x0 = (S[i]-x[U[i]]-x[V[i]])/2;
			s.insert(z[U[i]] ? -x0 : x0);
		}
	}
	if(s.size() > 1){
		cout << 0 << endl;
		return 0;
	}
	else if(s.size() == 1){
		//for(int i=0; i<N; i++) cout << z[i] << " " << x[i] << endl;
		ll x0 = *s.begin();
		f(x0, x, z, graph);
		bool ok=true;
		for(int i=0; i<N; i++){
			ok = ok && x[i] > 0;
		}
		for(int i=0; i<M; i++){
			ok = ok && (x[U[i]] + x[V[i]] == S[i]);
		}
		cout << (ok ? 1 : 0) << endl;
		return 0;
	}
	bool ok = true;
	for(int i=0; i<M; i++){
		ok = ok && (x[U[i]]+x[V[i]]==S[i]);
	}
	if(!ok){
		cout << 0 << endl;
		return 0;
	}

	ll lb=1, ub=INF;
	for(int i=0; i<N; i++){
		if(z[i]){
			ub = min(ub, x[i]-1);
		}
		else{
			lb = max(lb, -x[i]+1);
		}
	}
	cout << max(0LL, ub-lb+1) << endl;
	return 0;
}
