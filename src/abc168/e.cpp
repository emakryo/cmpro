#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
ostream& operator<<(ostream &os, vector<T> &v){
	string sep = " ";
	if(v.size()) os << v[0];
	for(int i=1; i<v.size(); i++) os << sep << v[i];
	return os;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
	cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__);
#else
#define dbg(...) 
#endif

struct rational {
	typedef long long ll;
	ll d, n;
	rational(ll denominator=0, ll nominator=1){
		d = denominator;
		n = nominator;
		if(d == 0) n = 1;
		else {
			ll g = gcd(abs(d), abs(n));
			d /= g;
			n /= g;
		}

		if(n<0){
			d=-d;
			n=-n;
		}
	}
	rational(pair<ll, ll> p): rational(p.first, p.second) {}
	// Caution: overflow
	bool operator< (const rational &o) const {
		return d*o.n<n*o.d;
		//return (*this)()<o();
	}
	bool operator== (const rational &o) const { return d==o.d&&n==o.n; }
	rational inv() const { return rational(n, d); }
	rational operator- () const { return rational(-d, n); }
	double operator()() const { return (double)d/n; }
	pair<ll, ll> to_pair() const {return {d, n};}
	ll gcd(ll x, ll y){
		if(y==0) return x;
		else return gcd(y, x%y);
	}
};

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

int main() {
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	vector<ll> a(n), b(n);
	for(int i=0; i<n; i++) cin >> a[i] >> b[i];

	int nz=0;
	int naz=0;
	int nbz=0;
	map<pair<ll, ll>, int> c;
	for(int i=0; i<n; i++) {
		if(a[i]==0&&b[i]==0){
			nz++;
		} else if(a[i]==0){
			naz++;
		} else if(b[i]==0){
			nbz++;
		} else {
			c[rational(a[i], b[i]).to_pair()]++;
		}
	}

	mint ans = mint(2).pow(naz) + mint(2).pow(nbz) - 1;
	for(auto p: c){
		int x=p.second;
		int y = c[(-rational(p.first).inv()).to_pair()];
		dbg(p.first.first, p.first.second, x, y);

		ans *= mint(2).pow(x) + mint(2).pow(y) - 1;
		c[p.first] = 0;
		c[(-rational(p.first).inv()).to_pair()] = 0;
	}

	ans += nz-1;
	cout << ans << endl;

	return 0;
}
