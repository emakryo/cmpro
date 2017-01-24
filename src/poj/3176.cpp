#include<iostream>
#include<algorithm>
using namespace std;
const int Nmax = 350;
int N;
int A[Nmax][Nmax];
long dp[Nmax+1][Nmax+1];

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		for(int j=0; j<=i; j++){
			cin >> A[i][j];
		}
	}

	for(int i=0; i<N; i++){
		for(int j=0; j<=i; j++){
			dp[i+1][j+1] = max(dp[i][j], dp[i][j+1]) + A[i][j];
			//cout << dp[i+1][j+1] << " ";
		}
		//cout << endl;
	}

	long ans = 0;
	for(int i=1; i<=N; i++) ans = max(ans, dp[N][i]);
	cout << ans << endl;

	return 0;
}
