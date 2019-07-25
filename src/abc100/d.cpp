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
const int Nmax = 1000;
int N, M;
ll X[Nmax], Y[Nmax], Z[Nmax];

int main(){
	cin >> N >> M;
	for(int i=0; i<N; i++) cin >> X[i] >> Y[i] >> Z[i];

	ll ans = -1e16;
	for(int k=0; k<8; k++){
		int s[3];
		vector<ll> x(N);
		for(int i=0; i<3; i++) s[i] = ((k>>i&1)<<1)-1;
		for(int i=0; i<N; i++) x[i] = s[0]*X[i]+s[1]*Y[i]+s[2]*Z[i];

		sort(x.begin(), x.end());
		reverse(x.begin(), x.end());
		ll tmp_ans = 0;
		for(int i=0; i<M; i++) tmp_ans += x[i];
		ans = max(ans, tmp_ans);
	}

	cout << ans << endl;

	return 0;
}
