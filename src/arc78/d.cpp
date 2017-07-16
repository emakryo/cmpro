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
const int Nmax = 100000;
int N, A[Nmax], B[Nmax];

void dfs1(int n, int d, int p, vector<vector<int> > &graph, vector<int> &depth){
	depth[n] = d;
	for(int i=0; i<graph[n].size(); i++){
		int m = graph[n][i];
		if(m == p) continue;
		dfs1(m, d+1, n, graph, depth);
	}
}

bool dfs2(int n, int p, vector<vector<int> > &graph, vector<bool> &path){
	if(n == N-1){
		path[n] = true;
		return true;
	}
	for(int i=0; i<graph[n].size(); i++){
		int m = graph[n][i];
		if(m == p) continue;
		if(dfs2(m, n, graph, path)){
			path[n] = true;
			return true;
		}
	}

	return false;
}

int dfs3(int n, int p, vector<vector<int> > &graph, int last, int next){
	int ret = 1;

	for(int i=0; i<graph[n].size(); i++){
		int m = graph[n][i];
		if(m == p) continue;
		if(n == last && m == next) continue;
		ret += dfs3(m, n, graph, last, next);
	}

	return ret;
}

int main(){
	cin >> N;
	vector<vector<int> > graph(N);
	for(int i=0; i<N-1; i++){
		cin >> A[i] >> B[i];
		A[i]--; B[i]--;
		graph[A[i]].push_back(B[i]);
		graph[B[i]].push_back(A[i]);
	}

	vector<int> depth(N);
	dfs1(0, 0, -1, graph, depth);

	vector<bool> path(N);
	dfs2(0, -1, graph, path);

	int dist = depth[N-1];
	int black, white;
	for(int i=0; i<N; i++){
		if(depth[i] == dist/2 && path[i]){
			black = i;
		}
		else if(depth[i] == dist/2+1 && path[i]){
			white = i;
		}
	}

	//cout << black+1 << " " << white+1 << endl;
	int nblack = dfs3(0, -1, graph, black, white);
	//cout << nblack << endl;

	cout << (nblack > N-nblack ? "Fennec" : "Snuke") << endl;

	return 0;
}
