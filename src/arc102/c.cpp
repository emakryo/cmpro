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
ll N, K;

int main(){
	cin >> N >> K;

	ll ans = 0;
	for(ll l=1; l<=2*N/K; l++){
		if(K%2==1 && l%2==1) continue;
		ll t = (2*N+K*l)/(2*K) - (2+K*l)/(2*K) + 1 - ((2+K*l)%(2*K)==0?0:1);
		ans += t*t;
	}
	cout << ans << endl;

	return 0;
}
