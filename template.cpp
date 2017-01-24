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
const int Nmax = 1000;
const int Kmax = 100;
int N,K;
ll dp[Kmax+1][Nmax+1];

int main(){
	scanf("%d%d", &N, &K);

	for(int i=0; i<=K; i++) dp[i][0] = 1;
	for(int i=1; i<=K; i++){
		for(int j=1; j<=N; j++){
			dp[i][j] = dp[i-1][j];
			if(j-i>=0){
				dp[i][j] += dp[i][j-i];
			}
		}
	}

	return 0;
}
