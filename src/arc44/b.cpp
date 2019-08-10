#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Nmax = 1e5;
int N, A[Nmax];
const ll P = 1e9+7;

ll mypow(ll x, ll y){
	if(y==0) return 1;
	if(y%2) return x*mypow(x, y-1)%P;
	ll z = mypow(x, y/2);
	return z*z%P;
}

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	if(A[0]!=0){
		cout << 0 << endl;
		return 0;
	}
	map<int, ll> cnt;
	cnt[0]=1;
	for(int i=1; i<N; i++){
		cnt[A[i]]++;
		if(A[i]==0){
			cout << 0 << endl;
			return 0;
		}
	}
	ll ans = 1;
	int max_depth = 1;
	for(auto p: cnt){
		max_depth = max(max_depth, p.first);
	}
	for(int i=1; i<=max_depth; i++){
		ans *= mypow((P+mypow(2, cnt[i-1])-1)%P, cnt[i]);
		ans %= P;
		ans *= mypow(2, (cnt[i]-1)*cnt[i]/2);
		ans %= P;
		//cout << i << " " << cnt[i] << " " << ans << endl;
	}

	cout << ans << endl;

	return 0;
}
