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
