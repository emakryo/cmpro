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
const ll P = 1e9+7;
ll dp[50][1<<18];

int main(){
	int N, X, Y, Z;
	cin >> N >> X >> Y >> Z;

	//for(int k=0; k<(1<<18);k++) dp[0][k] = 1;
	dp[0][0] = 1;
	for(int i=1; i<=N; i++){
		for(int k=0; k<(1<<18); k++){
			for(int n=1; n<=10; n++){
				int l=((1<<18)-1)&((k<<n)|(1<<(n-1)));
				if((l>>(Z-1))&(l>>(Y+Z-1))&(l>>(X+Y+Z-1))&1){
					continue;
				}
				dp[i][l] += dp[i-1][k];
				dp[i][l] %= P;
			}
		}
	}

	ll ans = 1;
	for(int i=0; i<N; i++){
		ans *= 10;
		ans %= P;
	}

	for(int k=0; k<(1<<18); k++){
		ans = (ans - dp[N][k] + P)%P;
		//if(dp[N][k] > 0) cout << k << " " << dp[N][k] << endl;
	}

	cout << ans << endl;

	return 0;
}
