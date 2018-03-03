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
const int Nmax = 32;
int W,H,N;
int X[Nmax], Y[Nmax];
pair<int, int> xs[Nmax], ys[Nmax];
map<int, int> xord, yord;
int memo[Nmax][Nmax][Nmax][Nmax];

int dfs(int xi, int xj, int yi, int yj){
	if(memo[xi][xj][yi][yj] >= 0) return memo[xi][xj][yi][yj];
	memo[xi][xj][yi][yj] = 0;
	for(int xk=xi+1; xk<xj; xk++){
		int n = xs[xk].second;
		int yk = yord[Y[n]];
		if(yk <= yi || yj <= yk) continue;
		int s = dfs(xi, xk, yi, yk) +
			dfs(xi, xk, yk, yj) +
			dfs(xk, xj, yi, yk) +
			dfs(xk, xj, yk, yj) +
			xs[xj].first - xs[xi].first +
			ys[yj].first - ys[yi].first - 3;
		memo[xi][xj][yi][yj] = max(memo[xi][xj][yi][yj], s);
	}
	return memo[xi][xj][yi][yj];
}

int main(){
	cin >> W >> H;
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> X[i] >> Y[i];
	}
	X[N] = 0;
	Y[N] = 0;
	X[N+1] = W+1;
	Y[N+1] = H+1;
	N += 2;

	for(int i=0; i<N; i++){
		xs[i] = make_pair(X[i], i);
		ys[i] = make_pair(Y[i], i);
	}
	sort(xs, xs+N);
	sort(ys, ys+N);
	for(int i=0; i<N; i++){
		xord[xs[i].first] = i;
		yord[ys[i].first] = i;
	}

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			for(int k=0; k<N; k++){
				for(int l=0; l<N; l++){
					memo[i][j][k][l] = -1;
				}
			}
		}
	}

	cout << dfs(0, N-1, 0, N-1) << endl;
	return 0;
}
