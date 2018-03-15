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
const ll P = 1e9+7;
const int Nmax = 1e5+10;
int N;
ll A[Nmax], T;

ll ext_gcd(ll a, ll b, ll &x, ll &y){
	if(b == 0){
		x = 1;
		y = 0;
		return a;
	}
	ll nx, ny;
	ll g = ext_gcd(b, a%b, nx, ny);
	x = ny;
	y = nx - a/b *ny;
	return g;
}

ll inv_mod(ll x, ll p){
	ll y,z;
	ext_gcd(x, p, y, z);
	return y>=0 ? y : p+(y%p);
}

int main(){
	cin >> N;
	for(int i=0; i<=N; i++) cin >> A[i];
	cin >> T;

	vector<ll> qi(N+1), qt(N+1), c(N+1);

	qi[0] = 1;
	for(int i=1; i<=N; i++){
		qi[0] = (P+(qi[0]*-i)%P)%P;
	}
	for(int i=1; i<=N; i++){
		qi[i] = ((qi[i-1] * i)%P * inv_mod(P-N+i-1, P))%P;
	}

	ll qprod = 1;
	for(int i=0; i<=N; i++){
		qprod = (qprod * (T-i)) % P;
	}
	for(int i=0; i<=N; i++){
		qt[i] = (qprod * inv_mod(T-i, P)) % P;
	}

	for(int i=0; i<=N; i++){
		c[i] = A[i] * inv_mod(qi[i], P) % P;
	}

	ll ans = 0;
	for(int i=0; i<=N; i++){
		ll y = (c[i]*qt[i])%P;
		ans = (ans+y)%P;
	}
	cout << ans << endl;

	return 0;
}
