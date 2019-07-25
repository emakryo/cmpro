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
const int Mmax = 1e5;
int N, M, A[Mmax], B[Mmax];
vector<vector<int>> graph;
vector<bool> visited;

void dfs(int n, vector<int> &path){
	visited[n] = true;
	for(int m: graph[n]){
		if(visited[m]) continue;
		path.push_back(m);
		dfs(m, path);
		break;
	}
}


int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++){
		cin >> A[i] >> B[i];
		A[i]--; B[i]--;
	}
	graph = vector<vector<int>>(N);

	for(int i=0; i<M; i++){
		graph[A[i]].push_back(B[i]);
		graph[B[i]].push_back(A[i]);
	}

	visited = vector<bool>(N);
	vector<int> path1, path2;
	path1.push_back(0);
	path2.push_back(0);
	dfs(0, path1);
	dfs(0, path2);


	vector<int> ans;
	for(int i=path1.size()-1; i>=0; i--) ans.push_back(path1[i]);
	for(int i=1; i<path2.size(); i++) ans.push_back(path2[i]);

	cout << ans.size() << endl;
	for(int i=0; i<ans.size(); i++) cout << ans[i]+1 << (i==ans.size()-1?'\n':' ');

	return 0;
}
