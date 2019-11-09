#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(any{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

const ll P = 998244353;
ll fact[400000];

// Extended Euclid's greatest common divisor algorithm
// Find (x, y, g)
// where $a*x + b*y = g$ and g is the greatest common divisor of (a, b)
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

// Modular inverse of x given modulo p, y
// x*y = 1 mod p
// <=> x*y + z*p = 1
ll inv_mod(ll x, ll p){
	ll y,z;
	ext_gcd(x, p, y, z);
	return y>=0 ? y : p+(y%p);
}


// Modular factorial of n, also counting p's appearance e
// n! = a * p^e
// return: a % p
// n! = n * (n-1) * ... * (k*p+1) *
//      (k*p) * (k*p-1) * ... ((k-1)*p+1) *
//      ...
//      p * (p-1) * ... * 2 * 1   (k = floor(n/p))
//    = (n%p) * ... * 1 *
//      (k*p) * (p-1) * ... * 1 *
//      p * (p-1) * ... * 1       (mod p, preserving p's multiples)
//    = (n%p)! * p^k * k! * (p-1)^k
//    = (n%p)! * p^k * k! * (p-1)^(k%2)
//
// From the facts:
//   (p-1)! = p-1 (mod p) (c.f. Willson's theorem)
//   (p-2)**2 = 1 (mod p)
ll fact_mod(ll n, ll p, ll &e){
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


// Modular combination (n, m) given module p
// (n, m) = n!/(n-m)!m!
//        = (a_n * p^(e_n)) / ((a_{n-m} * p^(e_{n-m}) * (a_m * p^e_m))
//        = a_n / (a_{n-m} * a_m) * p^(e_n - e_{n-m} - e_m)
ll comb_mod(ll n, ll m, ll p){
	ll e1,e2,e3;
	ll a1 = fact_mod(n, p, e1);
	ll a2 = fact_mod(m, p, e2);
	ll a3 = fact_mod(n-m, p, e3);

	if(e1 > e2+e3) return 0;
	else return a1*inv_mod(a2*a3%p, p)%p;
}

int main(){
	int N, A, B;
	ll K;
	cin >> N >> A >> B >> K;

	fact[0] = fact[1] = 1;
	for(int i=2; i<400000; i++) fact[i] = fact[i-1]*i%P;

	ll ans = 0;
	for(int i=0; i<=N; i++){
		if((K-(ll)i*A)%B) continue;
		ll j = (K-(ll)i*A)/B;
		if(j<0 || N<j) continue;

		ans += comb_mod(N, i, P) * comb_mod(N, j, P) % P;
		ans %= P;
	}

	cout << ans << endl;
	return 0;
}
