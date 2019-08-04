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
string S;
const ll P = 1e9+7;

int main(){
	cin >> S;
	int N = S.size();

	vector<vector<ll>> dp(N+1, vector<ll>(13));
	dp[0][0] = 1;
	for(int i=0; i<N; i++){
		for(int k=0; k<13; k++){
			if(S[i]=='?'){
				for(int d=0; d<10; d++){
					dp[i+1][(10*k+d)%13] += dp[i][k];
				}
			} else {
				dp[i+1][(10*k+(S[i]-'0'))%13] = dp[i][k];
			}
		}
		for(int k=0; k<13; k++) dp[i+1][k] %= P;
	}

	cout << dp[N][5] << endl;

	return 0;
}
