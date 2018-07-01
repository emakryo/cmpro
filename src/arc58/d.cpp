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
const int COMB_MAX = 300000;
ll fact[COMB_MAX];

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

ll fact_mod(ll n, ll p, ll &e){
	// n! = a * p^e
	// return = a % p
	if(n == 0){
		e = 0;
		return 1;
	}

	ll na = fact_mod(n/p, p, e);

	e += n/p;
	ll a = na * fact[n%p] % p;

	if((n/p)%2) a = a * (p-1)%p;
	return a;
}

ll comb_mod(ll n, ll m, ll p){
	ll e1,e2,e3;
	ll a1 = fact_mod(n, p, e1);
	ll a2 = fact_mod(m, p, e2);
	ll a3 = fact_mod(n-m, p, e3);

	if(e1 > e2+e3) return 0;
	else return a1*inv_mod(a2*a3%p, p)%p;
}

int main(){
	fact[0] = fact[1] = 1;
	for(int i=2; i<COMB_MAX; i++) fact[i] = fact[i-1]*i%P;

	int H, W, A, B;
	cin >> H >> W >> A >> B;

	ll all = comb_mod(W+H-2, W-1, P);
	for(int i=0; i<B; i++){
		ll x = comb_mod(i+H-A-1, i, P) * comb_mod(W-i-1+A-1, A-1, P) % P;
		all = (all + P - x) % P;
	}

	cout << all << endl;


	return 0;
}
