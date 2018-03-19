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
const int Mmax = 1000, Kmax = 400;
const ll INF = 1e16;
int N, M, K;
int A[Mmax], B[Mmax], C[Mmax];
int X[Kmax], Y[Kmax], Z[Kmax];

int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++){
		cin >> A[i] >> B[i] >> C[i];
		A[i]--; B[i]--;
	}
	cin >> K;
	for(int i=0; i<K; i++){
		cin >> X[i] >> Y[i] >> Z[i];
		X[i]--; Y[i]--;
	}

	vector<vector<ll> > graph(N, vector<ll>(N, INF));
	for(int i=0; i<M; i++){
		graph[A[i]][B[i]] = C[i];
		graph[B[i]][A[i]] = C[i];
	}

	vector<vector<ll> > dist(N, vector<ll>(N, INF));
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			dist[i][j] = graph[i][j];
		}
	}

	for(int k=0; k<N; k++){
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				ll d = dist[i][k] + dist[k][j];
				if(d < dist[i][j]){
					dist[i][j] = d;
				}
			}
		}
	}

	for(int k=0; k<K; k++){
		dist[X[k]][Y[k]] = min(dist[X[k]][Y[k]], (ll)Z[k]);
		dist[Y[k]][X[k]] = min(dist[Y[k]][X[k]], (ll)Z[k]);

		for(int l : {X[k], Y[k]}){
			for(int i=0; i<N; i++){
				for(int j=0; j<N; j++){
					ll d = dist[i][l] + dist[l][j];
					if(d < dist[i][j]){
						dist[i][j] = d;
					}
				}
			}
		}
		ll ans = 0;
		for(int i=0; i<N; i++){
			for(int j=i+1; j<N; j++){
				ans += dist[i][j];
				//cout << i << " " << j << " " << dist[i][j] << endl;
			}
		}
		cout << ans << endl;
	}

	return 0;
}
