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
const int Nmax = 2e5;
int N;
ll A[Nmax], B[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];
	for(int i=0; i<N; i++) cin >> B[i];

	ll ans = 0;
	for(int i=0; i<31; i++){
		vector<ll> bs(N);
		for(int j=0; j<N; j++) bs[j] = B[j]%(1LL<<(i+1));
		sort(bs.begin(), bs.end());
		//for(int i=0; i<N; i++) cout << bs[i] << (i<N-1?' ':'\n');
		ll k = 0;
		for(int j=0; j<N; j++){
			ll a = A[j]%(1LL<<(i+1));
			ll l1 = lower_bound(bs.begin(), bs.end(), (2LL<<i)-a)
				-lower_bound(bs.begin(), bs.end(), (1LL<<i)-a);
			ll l2 = lower_bound(bs.begin(), bs.end(), (4LL<<i)-a)
				-lower_bound(bs.begin(), bs.end(), (3LL<<i)-a);
			//if(l1>0||l2>0) cout << i << ":" << a << " "<< l1 << " " << l2 << endl;
			k += l1 + l2;
		}
		ans |= (k%2)<<i;
	}

	cout << ans << endl;

	return 0;
}
