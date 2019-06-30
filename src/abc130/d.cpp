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
int N, A[Nmax];
ll K;

int main(){
	cin >> N >> K;
	for(int i=0; i<N; i++) cin >> A[i];

	vector<ll> cum(N);
	cum[0] = A[0];
	for(int i=1; i<N; i++) cum[i] = cum[i-1]+A[i];

	ll ans = 0;
	for(int i=0; i<N; i++){
		auto j = lower_bound(cum.begin()+i, cum.end(), (i==0?0:cum[i-1])+K);
		ll n = cum.end() - j;
		//if(*j == cum[i]+K) n++;
		//cout << n << endl;
		ans += n;
	}

	cout << ans << endl;

	return 0;
}
