#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Nmax = 3000;
int N, A[Nmax];
ll fact[200000];

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

ll pow_mod(ll n, ll k, ll p){
	if(k==0) return 1;
	if(k%2) return n*pow_mod(n, k-1, p)%p;
	ll z = pow_mod(n, k/2, p);
	return z*z%p;
}

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	fact[0] = fact[1] = 1;
	for(int i=2; i<200000; i++) fact[i] = fact[i-1]*i%N;

	vector<int> inv(N);
	for(int i=1; i<N; i++) inv[i] = inv_mod(i, N);

	vector<int> ans(N);
	for(int i=0; i<N; i++){
		if(A[i]==0) continue;
		ans[0] += 1;
		int exp = 1;
		for(int j=0; j<N; j++){
			ans[N-1-j] += N-exp*fact[N-1]%N*inv[fact[j]*fact[N-1-j]%N]%N;
			ans[N-1-j] %= N;
			exp = exp*(N-i)%N;
		}
	}

	for(int i=0; i<N; i++) cout << ans[i] << (i==N-1?'\n':' ');

	return 0;
}
