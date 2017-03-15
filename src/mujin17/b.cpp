#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
int N;
string A[500];
int dist[1<<10];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	vector<int> nrow(N, 0);
	vector<int> ncol(N, 0);
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if(A[i][j] == '#'){
				nrow[i]++;
				ncol[j]++;
			}
		}
	}

	int max_row = nrow[0];
	for(int i=0; i<N; i++){
		max_row = max(max_row, nrow[i]);
	}

	int done_col = 0;
	for(int i=0; i<N; i++){
		if(ncol[i] == N) done_col++;
	}

	int ans = 1e6;
	for(int i=0; i<N; i++){
		if(ncol[i] > 0){
			ans = min(ans, N-nrow[i]+N-done_col);
		}
		else{
			ans = min(ans, N-nrow[i]+1+N-done_col);
		}
	}

	if(max_row == 0){
		cout << -1 << endl;
	}
	else{
		cout << ans << endl;
	}

	/*
	int n = 0;
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if(A[i][j] == '#'){
				n |= 1<<(i*N+j);
			}
		}
	}
	
	for(int i=0; i<(1<<10); i++) dist[i] = 1e8;
	dist[n] = 0;
	
	queue<int> que;
	que.push(n);
	while(!que.empty()){
		int x = que.front();
		que.pop();
		if(x == (1<<(N*N))-1){
			cout << dist[x] << endl;
			return 0;
		}
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				int y = x;
				for(int k=0; k<N; k++){
					y &= ~(1 << (k*N+j));
					y |= ((x >>(i*N+k))&1) << (k*N+j);
				}
				if(dist[y] == 1e8){
					//cout << y << endl;
					que.push(y);
					dist[y] = dist[x]+1;
				}
			}
		}
	}
	
	cout << -1 << endl;
	*/


	return 0;
}
