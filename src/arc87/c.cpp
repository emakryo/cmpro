#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Nmax = 1e5;
int N;
ll A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	map<ll, int> cnt;
	for(int i=0; i<N; i++) cnt[A[i]]++;

	ll ans = 0;
	for(auto p: cnt){
		ll x = p.first;
		int m = p.second;
		if(m >= x) ans += m-x;
		else ans += m;
	}

	cout << ans << endl;

	return 0;
}
