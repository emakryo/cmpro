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
const int Mmax = 1000;
int N, M, X[Mmax], Y[Mmax], Z[Mmax];
const int INF = 1e8;

void solve(){
	cin >> N >> M;
	for(int i=0; i<M; i++){
		cin >> X[i] >> Y[i] >> Z[i];
		X[i]--;
		Y[i]--;
	}
	vector<vector<int>> dist(N, vector<int>(N, INF));
	for(int i=0; i<M; i++){
		dist[X[i]][Y[i]] = Z[i];
		dist[Y[i]][X[i]] = Z[i];
	}

	for(int k=0; k<N; k++){
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				if(dist[i][k]+dist[k][j] < dist[i][j]){
					dist[i][j] = dist[i][k]+dist[k][j];
				}
			}
		}
	}

	for(int i=0; i<M; i++){
		if(dist[X[i]][Y[i]] < Z[i]){
			cout << "Impossible" << endl;
			return;
		}
	}

	cout << M << endl;
	for(int i=0; i<M; i++){
		cout << X[i]+1 << " " << Y[i]+1 << " " << Z[i] << endl;
	}
}

int main(){
	int T;
	cin >> T;
	for(int i=0; i<T; i++){
		cout << "Case #" << i+1 << ": ";
		solve();
	}

	return 0;
}
