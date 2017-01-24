#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const long INF = 1e18;
const int Nmax = 200;
const int Mmax = 10000;
const int Rmax = 1000;
int N, M, R;
int X[Mmax], Y[Mmax], C[Mmax], SL[Mmax];
int Z[Rmax];
long sd[Nmax][Nmax], ld[Nmax][Nmax];
long dp[Rmax][Nmax];

int solve(){
	cin >> N >> M;
	if(N==0 && M==0) return -1;
	for(int i=0; i<M; i++){
		char sl;
		cin >> X[i] >> Y[i] >> C[i] >> sl;
		SL[i] = sl == 'S' ? 0 : 1;
		X[i]--; Y[i]--;
	}
	cin >> R;
	for(int i=0; i<R; i++) {
		cin >> Z[i];
		Z[i]--;
	}

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			sd[i][j] = INF;
			ld[i][j] = INF;
		}
		sd[i][i] = 0;
		ld[i][i] = 0;
	}

	for(int i=0; i<M; i++){
		if(SL[i] == 0){
			sd[X[i]][Y[i]] = C[i];
			sd[Y[i]][X[i]] = C[i];
		}
		else{
			ld[X[i]][Y[i]] = C[i];
			ld[Y[i]][X[i]] = C[i];
		}
	}

	for(int k=0; k<N; k++){
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				sd[i][j] = min(sd[i][j], sd[i][k]+sd[k][j]);
			}
		}
	}

	for(int k=0; k<N; k++){
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				ld[i][j] = min(ld[i][j], ld[i][k]+ld[k][j]);
			}
		}
	}


	for(int i=0; i<R; i++){
		for(int j=0; j<N; j++){
			dp[i][j] = INF;
		}
	}
	
	dp[0][Z[0]] = 0;
	for(int i=1; i<R; i++){
		for(int j=0; j<N; j++){
			for(int k=0; k<N; k++){
				long di = ld[Z[i-1]][k]+sd[k][j]+ld[j][Z[i]];
				if(j==k) di = min(di, ld[Z[i-1]][Z[i]]);
				dp[i][j] = min(dp[i][j], dp[i-1][k]+di);
			}
		}
	}

	/*
	for(int i=0; i<R; i++){
		for(int j=0; j<N; j++){
			cout << dp[j][i] << " ";
		}
		cout << endl;
	}
	*/

	long ans = INF;
	for(int i=0; i<N; i++){
		ans = min(ans, dp[R-1][i]);
	}

	cout << ans << endl;
	return 0;
}

int main(){
	ios_base::sync_with_stdio(false);
	while(solve()==0){}
	return 0;
}
