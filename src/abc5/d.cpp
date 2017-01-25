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
int N, D[50][50], Q, P[2500];
int cum[51][51];
int maxp[2501];

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			cin >> D[i][j];
		}
	}
	cin >> Q;
	for(int i=0; i<Q; i++) cin >> P[i];


	for(int i=1; i<=N; i++){
		for(int j=1; j<=N; j++){
			cum[i][j] = D[i-1][j-1] + cum[i][j-1] + cum[i-1][j] - cum[i-1][j-1];
		}
	}

	for(int i=1; i<=N*N; i++){
		maxp[i] = maxp[i-1];
		for(int j=1; j<=i; j++){
			if(i%j!=0) continue;
			for(int x=1; x<=N; x++){
				for(int y=1; y<=N; y++){
					int x0 = x-j;
					int y0 = y-i/j;
					if(x0<0 || y0<0) continue;
					maxp[i] = max(maxp[i], cum[x][y]-cum[x0][y]-cum[x][y0]+cum[x0][y0]);
				}
			}
		}
	}

	for(int i=0; i<Q; i++){
		cout << maxp[P[i]] << endl;
	}

	return 0;
}
