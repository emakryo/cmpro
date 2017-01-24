#include<iostream>
#include<vector>
using namespace std;
const int Max = 401;
int N,C,A[Max],B[Max];
long dp[Max][Max];
long sp[Max][Max];

int main(){
	long p = 1000000007;
	cin >> N >> C;
	for(int i=0; i<N; i++) cin >> A[i];
	for(int i=0; i<N; i++) cin >> B[i];

	for(int i=1; i<Max; i++){
		long k = i;
		for(int j=0; j<Max; j++){
			// dp[i][j] = \sum_k=1^i k^j
			sp[i][j] = (sp[i-1][j] + k)%p;
			k = k*i%p;
		}
	}

	dp[0][0] = 1;
	for(int i=1; i<=N; i++){
		dp[i][0] = 1;
		for(int j=1; j<=C; j++){
			long pow = 1;
			for(int k=0; k<=j; k++){
				dp[i][j] = (dp[i][j]+dp[i-1][j-k]*(sp[B[i-1]][k]-sp[A[i-1]][k]))%p;
			}
		}
	}

	cout << dp[N][C] << endl;
}
