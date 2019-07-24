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
ll M, A[Nmax];

int main(){
	cin >> N >> M;
	for(int i=0; i<N; i++) cin >> A[i];

	vector<ll> cum(N+1);
	for(int i=0; i<N; i++) cum[i+1] = (cum[i]+A[i])%M;
	map<ll, int> cnt;
	for(int i=0; i<=N; i++) cnt[cum[i]]++;

	ll ans = 0;
	for(auto p: cnt){
		ll m = p.second;
		ans += m*(m-1)/2;
	}

	cout << ans << endl;

	return 0;
}
