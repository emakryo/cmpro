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
const int Cmax = 30, Nmax = 500;
int N, C, D[Cmax][Cmax], X[Nmax][Nmax];
int d[Cmax][3];

int main(){
	cin >> N >> C;
	for(int i=0; i<C; i++){
		for(int j=0; j<C; j++) cin >> D[i][j];
	}
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			cin >> X[i][j];
			X[i][j]--;
		}
	}

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			for(int k=0; k<C; k++){
				d[k][(i+j)%3] += D[X[i][j]][k];
			}
		}
	}

	ll ans = 1e16;
	for(int i=0; i<C; i++){
		for(int j=0; j<C; j++){
			if(i==j) continue;
			for(int k=0; k<C; k++){
				if(i==k||j==k) continue;
				ans = min(ans, (ll)d[i][0]+d[j][1]+d[k][2]);
			}
		}
	}

	cout << ans << endl;

	return 0;
}
