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
int N;
ll C, X[Nmax], V[Nmax];

int main(){
	cin >> N >> C;
	for(int i=0; i<N; i++) cin >> X[i] >> V[i];

	vector<ll> rmax1(N);
	vector<ll> rmax2(N);
	vector<ll> lmax1(N);
	vector<ll> lmax2(N);
	ll rcum = V[0], lcum = V[N-1];
	rmax1[0] = max(0LL, V[0]-X[0]);
	rmax2[0] = max(0LL, V[0]-2*X[0]);
	lmax1[0] = max(0LL, V[N-1]-(C-X[N-1]));
	lmax2[0] = max(0LL, V[N-1]-2*(C-X[N-1]));
	for(int i=1; i<N; i++){
		rcum += V[i];
		lcum += V[N-1-i];
		rmax1[i] = max(rmax1[i-1], rcum-X[i]);
		rmax2[i] = max(rmax2[i-1], rcum-2*X[i]);
		lmax1[i] = max(lmax1[i-1], lcum-(C-X[N-i-1]));
		lmax2[i] = max(lmax2[i-1], lcum-2*(C-X[N-i-1]));
	}

	ll ans = max(rmax1[N-1], lmax1[N-1]);
	for(int i=0; i<N-1; i++){
		ans = max(ans, rmax1[N-i-2]+lmax2[i]);
		ans = max(ans, lmax1[N-i-2]+rmax2[i]);
	}

	cout << ans << endl;

	return 0;
}
