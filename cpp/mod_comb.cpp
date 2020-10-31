#include<bits/stdc++.h>

// Extended Euclid's greatest common divisor algorithm
// Find (x, y, g)
// where $a*x + b*y = g$ and g is the greatest common divisor of (a, b)
long long ext_gcd(long long a, long long b, long long &x, long long &y){
	if(b == 0){
		x = 1; y = 0; return a;
	}
	long long nx, ny;
	long long g = ext_gcd(b, a%b, nx, ny);
	x = ny; y = nx - a/b *ny;
	return g;
}

struct mint {
	typedef long long ll;
	ll x, m;
	mint(ll x=0, ll m=1e9+7): x((m+x%m)%m), m(m) {}
	mint operator-() const { return mint(m-x, m); }
	mint& operator+=(const mint o) { x=(x+o.x)%m; return *this; }
	mint& operator+=(const ll o) { return (*this)+=mint(o, m); }
	mint& operator-=(const mint o) { return (*this)+=(-o); }
	mint& operator-=(const ll o) { return (*this)-=mint(o, m); }
	mint& operator*=(const mint o) { x = x*o.x%m; return *this; }
	mint& operator*=(const ll o) { return (*this)*=mint(o, m); }
	mint& operator/=(const mint o) { return (*this)*=o.inv(); }
	mint& operator/=(const ll o) { return (*this)/=mint(o, m); }
	friend mint operator+(mint l, const mint r) { l+=r; return l; }
	friend mint operator+(mint l, const ll r) { l+=r; return l; }
	friend mint operator+(const ll l, mint r) { r+=l; return r; }
	friend mint operator-(mint l, const mint r) { l-=r; return l; }
	friend mint operator-(mint l, const ll r) { l-=r; return l; }
	friend mint operator-(const ll l, mint r) { r-=l; return r; }
	friend mint operator*(mint l, const mint r) { l*=r; return l; }
	friend mint operator*(mint l, const ll r) { l*=r; return l; }
	friend mint operator*(const ll l, mint r) { r*=l; return r; }
	friend mint operator/(mint l, const mint r) { l/=r; return l; }
	friend mint operator/(mint l, const ll r) { l/=r; return l; }
	friend mint operator/(const ll l, const mint r) { return mint(l, r.m)/r; }
	bool operator==(const mint o) const { return x==o.x; }
	bool operator!=(const mint o) const { return x!=o.x; }
	friend bool operator==(const ll l, const mint r) { return mint(l, r.m) == r; }
	friend bool operator!=(const ll l, const mint r) { return mint(l, r.m) != r; }
	friend std::ostream& operator<<(std::ostream &os, const mint x) { return os << x.x; }

	mint pow(ll k) const {
		if(k==0) return mint(1, m);
		if(k%2) return pow(k-1)*x;
		mint z = pow(k/2); return z*z;
	}

	mint inv() const {
		ll y,z;
		ext_gcd(x, m, y, z);
		return mint(y, m);
	}
};

struct Comb {
	typedef long long ll;
	std::vector<mint> fact, fact_inv;
	ll mod;
	Comb(int n_max=2000005, ll m=1e9+7): mod(m) {
		fact.emplace_back(1, m);
		fact_inv.emplace_back(1, m);
		for(int i=1; i<std::min((ll)n_max, mod); i++){
			fact.push_back(fact[i-1] * i);
			fact_inv.push_back(fact[i].inv());
		}
	}
	mint operator() (ll n, ll m) const {
		if(n < mod){
			return fact[n] * fact_inv[m] * fact_inv[n-m];
		} else {
			return comb_ext(n, m);
		}
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
	mint fact_ext(ll n, ll &e) const {
		if(n == 0){
			e = 0;
			return mint(1, mod);
		}

		mint na = fact_ext(n/mod, e);
		e += n/mod;
		mint a = na * fact[n%mod];
		if((n/mod)%2) a = a * (mod-1);
		return a;
	}

// Modular combination (n, m) given module p
// (n, m) = n!/(n-m)!m!
//        = (a_n * p^(e_n)) / ((a_{n-m} * p^(e_{n-m}) * (a_m * p^e_m))
//        = a_n / (a_{n-m} * a_m) * p^(e_n - e_{n-m} - e_m)
	mint comb_ext (ll n, ll m) const {
		ll e1,e2,e3;
		mint a1 = fact_ext(n, e1);
		mint a2 = fact_ext(m, e2);
		mint a3 = fact_ext(n-m, e3);

		if(e1 > e2+e3) return 0;
		else return a1*(a2*a3).inv();
	}
};
