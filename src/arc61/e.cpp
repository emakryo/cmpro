#include<iostream>
#include<queue>
#include<vector>
#include<map>
using namespace std;
typedef pair<int, int> cv;
const int Mmax = 200001;
const int INF = 1e8;
int N,M;
int P[Mmax],Q[Mmax],C[Mmax];

int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++){
		cin >> P[i] >> Q[i] >> C[i];
	}

	map<pair<int,int>, int> encode;
	int n=0;
	for(int i=1; i<=N; i++){
		encode[make_pair(i,-1)] = n++;
	}
	for(int i=0; i<M; i++){
		if(encode.find(make_pair(P[i],C[i])) == encode.end()){
			encode[make_pair(P[i],C[i])] = n++;
		}
		if(encode.find(make_pair(Q[i],C[i])) == encode.end()){
			encode[make_pair(Q[i],C[i])] = n++;
		}
	}
	vector<vector<pair<int, int> > > to(n);
	for(int i=0; i<M; i++){
		to[encode[make_pair(P[i],-1)]].push_back(make_pair(1,encode[make_pair(Q[i],C[i])]));
		to[encode[make_pair(Q[i],-1)]].push_back(make_pair(1,encode[make_pair(P[i],C[i])]));
		to[encode[make_pair(P[i],C[i])]].push_back(make_pair(0,encode[make_pair(Q[i],C[i])]));
		to[encode[make_pair(Q[i],C[i])]].push_back(make_pair(0,encode[make_pair(P[i],C[i])]));
		to[encode[make_pair(P[i],C[i])]].push_back(make_pair(0,encode[make_pair(P[i],-1)]));
		to[encode[make_pair(Q[i],C[i])]].push_back(make_pair(0,encode[make_pair(Q[i],-1)]));
	}

	vector<int> cost(n,INF);
	cost[encode[make_pair(1,-1)]] = 0;
	priority_queue<cv, vector<cv>, greater<cv> > que;
	que.push(make_pair(0, encode[make_pair(1,-1)]));
	while(!que.empty()){
		int v = que.top().second;
		que.pop();
		for(int i=0; i<to[v].size(); i++){
			int c = to[v][i].first;
			int u = to[v][i].second;
			if(cost[u] > cost[v]+c){
				cost[u] = cost[v]+c;
				que.push(make_pair(cost[u],u));
			}
		}
	}

	if(cost[encode[make_pair(N,-1)]] == INF){
		cout << -1 << endl;
	}
	else {
		cout << cost[encode[make_pair(N,-1)]] << endl;
	}
	return 0;
}
