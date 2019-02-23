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
const int Nmax=1e5;
const int C[9] = {2,5,5,4,5,6,3,7,6};
int N, M, A[9];
int dp[Nmax][9], b[9];

int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++){
		cin >> A[i];
		A[i]--;
		b[A[i]] = 1;
	}

	for(int i=1; i<N+1; i++){
		for(int j=0; j<9; j++) dp[i][j] = -1;
		for(int j=0; j<9; j++){
			if(!b[j]) continue;
			for(int k=0; k<9; k++){
				if(i-C[j]>=0 && dp[i-C[j]][k]>=0) dp[i][j] = max(dp[i-C[j]][k]+1, dp[i][j]);
			}
		}
	}

	/*
	for(int i=0; i<N+1; i++){
		for(int j=0; j<9; j++){
			cout << dp[i][j] << (j==8?'\n':'\t');
		}
	}
	*/

	int len=0;
	for(int j=0; j<9; j++) len=max(dp[N][j], len);
	//cout << len << endl;

	int i=N;
	while(i>0){
		for(int j=8; j>=0; j--){
			if(dp[i][j]==len){
				len--;
				//cout << j+1 << ' ' << i << endl;
				cout << j+1;
				i -= C[j];
				break;
			}
		}
	}
	cout << endl;

	return 0;
}
