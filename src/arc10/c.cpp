#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
#include<sstream>
using namespace std;
typedef long long ll;
const int Mmax = 10;
const int Nmax = 5000;
int N,M,Y,Z,P[Mmax];
char C[Mmax];
string B;
int Bn[Nmax];
ll dp[2][Mmax+1][1<<(Mmax+1)];

int main(){
	cin >> N >> M >> Y >> Z;
	string tmp;
	getline(cin, tmp);
	for(int i=0; i<M; i++){
		getline(cin, tmp);
		stringstream ss(tmp);
		ss >> C[i] >> P[i];
	}
	getline(cin, B);

	int conv[26];
	for(int i=0; i<M; i++){
		conv[C[i]-'A'] = i;
	}

	for(int i=0; i<N; i++){
		Bn[i] = conv[B[i]-'A'];
	}

	for(int i=0; i<=M; i++){
		for(int j=0; j<(1<<(M+1)); j++){
			dp[0][i][j] = dp[1][i][j] = -1L<<50;
		}
	}
	dp[1][M][0] = dp[0][M][0] = 0;

	for(int i=0; i<N; i++){
		for(int j=0; j<=M; j++){
			for(int k=0; k<(1<<(M+1)); k++){
				dp[i%2][j][k] = dp[1-i%2][j][k];
			}
		}

		for(int j=0; j<=M; j++){
			for(int k=0; k<(1<<(M+1)); k++){
				ll x = dp[1-i%2][j][k]+P[Bn[i]];
				if(Bn[i] == j) x += Y;
				dp[i%2][Bn[i]][k|(1<<Bn[i])] = max(dp[i%2][Bn[i]][k|(1<<Bn[i])], x);
				//cout << i << " " << Bn[i] << " " << (k|(1<<j)) << " " << dp[i%2][Bn[i]][k|(1<<Bn[i])] << endl;
			}
		}
	}

	for(int i=0; i<M; i++){
		dp[(N-1)%2][i][(1<<M)-1] += Z;
	}

	ll ans=0;
	for(int i=0; i<=M; i++){
		for(int j=0; j<(1<<(M+1)); j++){
			ans = max(ans, dp[(N-1)%2][i][j]);
		}
	}

	cout << ans << endl;

	return 0;
}
