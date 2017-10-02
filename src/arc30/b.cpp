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
const int Nmax = 100;
int N, X, H[Nmax], A[Nmax], B[Nmax];

int rec(int x, vector<vector<int> > &graph, vector<bool> &visit){
	int ret = 0;
	visit[x] = true;
	for(int i=0; i<graph[x].size(); i++){
		if(visit[graph[x][i]]) continue;
		ret += rec(graph[x][i], graph, visit);
	}

	if(ret > 0 || H[x] > 0) ret += 2;

	//cout << ret << " " << x << endl;
	return ret;
}

int main(){
	cin >> N >> X;
	for(int i=0; i<N; i++) cin >> H[i];
	for(int i=0; i<N-1; i++) cin >> A[i] >> B[i];

	vector<vector<int> > graph(N);
	for(int i=0; i<N-1; i++){
		graph[A[i]-1].push_back(B[i]-1);
		graph[B[i]-1].push_back(A[i]-1);
	}
	vector<bool> visit(N, false);

	cout << max(rec(X-1, graph, visit)-2, 0) << endl;

	return 0;
}
