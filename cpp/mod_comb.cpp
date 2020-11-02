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

template<long long m=1000000007>
struct mint {
	typedef long long ll;
	ll x;
	static constexpr ll mod() { return m; }
	constexpr mint(ll x=0): x((m+x%m)%m) {}
	mint<m> operator-() const { return mint(m-x); }
	mint<m>& operator+=(const mint<m> o) { x=(x+o.x)%m; return *this; }
	mint<m>& operator+=(const ll o) { return (*this)+=mint(o); }
	mint<m>& operator-=(const mint<m> o) { return (*this)+=(-o); }
	mint<m>& operator-=(const ll o) { return (*this)-=mint(o); }
	mint<m>& operator*=(const mint<m> o) { x = x*o.x%m; return *this; }
	mint<m>& operator*=(const ll o) { return (*this)*=mint(o); }
	mint<m>& operator/=(const mint<m> o) { return (*this)*=o.inv(); }
	mint<m>& operator/=(const ll o) { return (*this)/=mint(o); }
	friend mint<m> operator+(mint<m> l, const mint<m> r) { l+=r; return l; }
	friend mint<m> operator+(mint<m> l, const ll r) { l+=r; return l; }
	friend mint<m> operator+(const ll l, mint<m> r) { r+=l; return r; }
	friend mint<m> operator-(mint<m> l, const mint<m> r) { l-=r; return l; }
	friend mint<m> operator-(mint<m> l, const ll r) { l-=r; return l; }
	friend mint<m> operator-(const ll l, mint<m> r) { r-=l; return r; }
	friend mint<m> operator*(mint<m> l, const mint<m> r) { l*=r; return l; }
	friend mint<m> operator*(mint<m> l, const ll r) { l*=r; return l; }
	friend mint<m> operator*(const ll l, mint<m> r) { r*=l; return r; }
	friend mint<m> operator/(mint<m> l, const mint<m> r) { l/=r; return l; }
	friend mint<m> operator/(mint<m> l, const ll r) { l/=r; return l; }
	friend mint<m> operator/(const ll l, const mint<m> r) { return mint(l)/r; }
	bool operator==(const mint<m> o) const { return x==o.x; }
	bool operator!=(const mint<m> o) const { return x!=o.x; }
	friend bool operator==(const ll l, const mint<m> r) { return mint<m>(l) == r; }
	friend bool operator!=(const ll l, const mint<m> r) { return mint<m>(l) != r; }
	friend std::ostream& operator<<(std::ostream &os, const mint<m> x) { return os << x.x; }

	mint<m> pow(ll k) const {
		if(k==0) return mint<m>(1);
		if(k%2) return pow(k-1)*x;
		mint<m> z = pow(k/2); return z*z;
	}

	mint<m> inv() const {
		ll y,z;
		ext_gcd(x, m, y, z);
		return mint<m>(y);
	}
};

template<long long m=1000000007>
struct Comb {
	typedef long long ll;
	std::vector<mint<m>> fact, fact_inv;
	Comb(int n_max=2000005) {
		fact.assign(n_max, 0);
		fact_inv.assign(n_max, 0);
		fact[0] = 1;
		fact_inv[0] = 1;
		for(int i=1; i<std::min((ll)n_max, m); i++){
			fact[i] = fact[i-1] * i;
			fact_inv[i] = fact[i].inv();
		}
	}
	mint<m> operator() (ll n, ll k) const {
		if(n < m){
			return fact[n] * fact_inv[k] * fact_inv[n-k];
		} else {
			return comb_ext(n, k);
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
	mint<m> fact_ext(ll n, ll &e) const {
		if(n == 0){
			e = 0;
			return mint<m>(1);
		}

		mint<m> na = fact_ext(n/m, e);
		e += n/m;
		mint<m> a = na * fact[n%m];
		if((n/m)%2) a = a * (m-1);
		return a;
	}

// Modular combination (n, m) given module p
// (n, m) = n!/(n-m)!m!
//        = (a_n * p^(e_n)) / ((a_{n-m} * p^(e_{n-m}) * (a_m * p^e_m))
//        = a_n / (a_{n-m} * a_m) * p^(e_n - e_{n-m} - e_m)
	mint<m> comb_ext (ll n, ll k) const {
		ll e1,e2,e3;
		mint<m> a1 = fact_ext(n, e1);
		mint<m> a2 = fact_ext(k, e2);
		mint<m> a3 = fact_ext(n-k, e3);

		if(e1 > e2+e3) return 0;
		else return a1*(a2*a3).inv();
	}
};
