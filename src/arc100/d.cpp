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
const int Nmax = 200000;
int N;
ll A[Nmax];


int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	vector<ll> cum(N);
	cum[0] = A[0];
	for(int i=1; i<N; i++){
		cum[i] = cum[i-1]+A[i];
	}

	int j=0;
	int k=2;
	ll ans = 1e18;
	for(int i=1; i<N-2; i++){
		while(j < i-1 &&
				abs(cum[j]-(cum[i]-cum[j])) > abs(cum[j+1]-(cum[i]-cum[j+1]))) j++;
		k = max(k, i+1);
		while(k < N-1 &&
				abs(cum[k]-cum[i]-(cum[N-1]-cum[k])) > abs(cum[k+1]-cum[i]-(cum[N-1]-cum[k+1]))) k++;
		//cout << j << " " << i << " " << k << endl;
		ll a = max(max(cum[j],cum[i]-cum[j]), max(cum[k]-cum[i], cum[N-1]-cum[k]));
		ll b = min(min(cum[j],cum[i]-cum[j]), min(cum[k]-cum[i], cum[N-1]-cum[k]));
		ans = min(ans, a-b);
	}

	cout << ans << endl;

	return 0;
}
