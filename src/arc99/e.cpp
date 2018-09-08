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
const int Mmax = 500000;
int N, M, A[Mmax], B[Mmax];

pair<int, int> dfs(int n, vector<int> &vec, vector<vector<int> > &g){
	pair<int, int> p = make_pair(1, 0);
	for(int m=0; m<g.size(); m++){
		if(g[n][m]==0) continue;
		if(vec[m]==vec[n]){
			return make_pair(-1, -1);
		}
		if(vec[m]==0){
			vec[m] = -vec[n];
			pair<int, int> q=dfs(m, vec, g);
			if(q.first < 0) return q;
			p.first += q.second;
			p.second += q.first;
		}
	}

	return p;
}


int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++){
		cin >> A[i] >> B[i];
		A[i]--; B[i]--;
	}

	vector<vector<int> > g(N, vector<int>(N, 1));

	for(int i=0; i<M; i++){
		g[A[i]][B[i]] = 0;
		g[B[i]][A[i]] = 0;
	}
	for(int i=0; i<N; i++){
		g[i][i] = 0;
	}

	vector<int> vec(N);
	vector<pair<int, int> > ps;
	for(int i=0; i<N; i++){
		if(vec[i]) continue;
		vec[i] = 1;
		pair<int, int> p = dfs(i, vec, g);
		if(p.first < 0) {
			cout << -1 << endl;
			return 0;
		}
		ps.push_back(p);
	}

	/*
	for(int i=0; i<ps.size(); i++){
		cout << ps[i].first << " " << ps[i].second << endl;
	}
	*/

	vector<vector<bool> > dp(ps.size()+1, vector<bool>(N+1));
	dp[0][0] = true;
	for(int i=0; i<ps.size(); i++){
		for(int j=0; j<=N; j++){
			dp[i+1][j+ps[i].first] = dp[i][j] || dp[i+1][j+ps[i].first];
			dp[i+1][j+ps[i].second] = dp[i][j] || dp[i+1][j+ps[i].second];
		}
	}

	/*
	for(int i=0; i<N+1; i++){
		if(dp[ps.size()][i]){
			cout << i << endl;
		}
	}
	*/

	int ans = 1e8;
	for(int i=0; i<N+1; i++){
		if(dp[ps.size()][i]){
			ans = min(ans, i*(i-1)/2 + (N-i)*(N-i-1)/2);
		}
	}

	cout << ans << endl;

	return 0;
}
