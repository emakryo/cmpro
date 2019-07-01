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
	for(int b=K+1; b<=N; b++){
		ll q = (N+1-(N+1)%b)/b;
		ll a0 = (K==0)?b-K-1:b-K;
		ll a1 = (b-K)*(q-1);
		ll a2 = max(0LL, (N+1)%b-K);
		//cout << b << " " << a0 << " " << a1 << " " << a2 << endl;
		ans += a0 + a1 + a2;
	}

	cout << ans << endl;

	return 0;
}
