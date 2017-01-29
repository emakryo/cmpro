//#include<iostream>
//#include<iomanip>
#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 300;
const int Mmax = 10000;
int N, M;
int c[Nmax];
int graph[Nmax][Nmax];
int dist[Nmax][Nmax];

int main(){
	scanf("%d%d", &N, &M);
	for(int i=0; i<M; i++){
		int mi;
		scanf("%d", &mi);
		for(int j=0; j<mi; j++){
			scanf("%d", &c[j]);
			c[j]--;
		}
		for(int j=0; j<mi; j++){
			for(int k=j+1; k<mi; k++){
				graph[c[j]][c[k]] = 1;
				graph[c[k]][c[j]] = 1;
			}
		}
	}

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			dist[i][j] = graph[i][j] > 0 ? graph[i][j] : 1e9;
		}
	}
	for(int i=0; i<N; i++){
		dist[i][i] = 0;
	}

	for(int k=0; k<N; k++){
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
			}
		}
	}

	int ans = 1e9;
	for(int i=0; i<N; i++){
		int sum = 0;
		for(int j=0; j<N; j++){
			if(j==i) continue;
			sum += dist[i][j];
		}
		ans = min(ans, sum);
	}

	printf("%d\n", (int)(100.0*ans/(N-1)));

	return 0;
}
