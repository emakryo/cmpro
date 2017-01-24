#include<iostream>
using namespace std;
typedef long long ll;
ll fact[100];

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
	while(y < 0) y+=p;
	return y;
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
	ll p = 7;
	fact[0] = fact[1] = 1;
	for(int i=2; i<100; i++) fact[i] = fact[i-1]*i%p;
	cout << comb_mod(13, 3, p) << endl;
	return 0;
}
