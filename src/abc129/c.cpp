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
const int Nmax = 1e5;
const ll P = 1e9+7;
int N, M, A[Nmax];

int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++) cin >> A[i];

	vector<ll> dp(N+1);
	dp[0] = 1;

	for(int i=0; i<N; i++){
		auto lb = lower_bound(A, A+M, i+1);
		if(lb != A+M && *lb == i+1){
			dp[i+1] = 0;
		} else {
			dp[i+1] = (dp[i] + (i==0?0:dp[i-1])) % P;
		}
		//cout << i+1 << " " << dp[i+1] << endl;
	}

	cout << dp[N] << endl;

	return 0;
}
