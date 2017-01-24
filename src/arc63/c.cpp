#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int Nmax = 1e5;
int N,K,A[Nmax],B[Nmax],V[Nmax],P[Nmax];
vector<int> graph[Nmax];
long upper[Nmax], lower[Nmax], depth[Nmax];

int dfs(int node, int par){
	depth[node] = par >= 0 ? depth[par]+1 : 0;
	for(int i=0; i<graph[node].size(); i++){
		if(graph[node][i] == par) continue;
		//cout << node << " " << graph[node][i] << endl;
		if(dfs(graph[node][i], node)) return 1;
		lower[node] = max(lower[node], lower[graph[node][i]]-1);
		upper[node] = min(upper[node], upper[graph[node][i]]+1);
	}

	if(lower[node] > upper[node]) return 1;
	return 0;
}

void dfs2(int node, int par){
	for(int i=0; i<graph[node].size(); i++){
		if(graph[node][i] == par) continue;
		lower[graph[node][i]] = max(lower[graph[node][i]], lower[node]-1);
		upper[graph[node][i]] = min(upper[graph[node][i]], upper[node]+1);
		dfs2(graph[node][i], node);
	}
}

int main(){
	cin >> N;
	for(int i=0; i<N-1; i++){
		cin >> A[i] >> B[i];
		A[i]--; B[i]--;
	}
	cin >> K;
	for(int i=0; i<K; i++){
		cin >> V[i] >> P[i];
		V[i]--;
	}

	for(int i=0; i<N-1; i++){
		graph[A[i]].push_back(B[i]);
		graph[B[i]].push_back(A[i]);
	}
	for(int i=0; i<N; i++){
		lower[i] = -1e7;
		upper[i] = 1e7;
	}
	for(int i=0; i<K; i++){
		upper[V[i]] = lower[V[i]] = P[i];
	}

	if(dfs(V[0],-1)){
		cout << "No" << endl;
		return 0;
	}

	for(int i=0; i<K; i++){
		//cout << P[i] << " " << depth[V[i]] << endl;
		if(P[0]%2 != (P[i]+depth[V[i]])%2){
			cout << "No" << endl;
			return 0;
		}
	}

	dfs2(V[0], -1);

	cout << "Yes" << endl;
	for(int i=0; i<N; i++){
		cout << lower[i] /*<< " " << upper[i]*/ << endl;
	}
}
