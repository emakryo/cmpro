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

template<typename T>
istream& operator>>(istream &is, vector<T> &v){
	for(int i=0; i<v.size(); i++) is >> v[i];
	return is;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
	cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__)
#else
#define dbg(...)
#endif


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

int _main(){
	for(auto x: std::vector<int>{3, 5, 7, 11, 13, 17, 19}){
		assert((mint(4, x)/mint(4, x))==1);
	}
	return 0;
}

int n, k;
vector<ll> a;

ll solve() {
	sort(a.begin(), a.end());

	mint ans = 1;
	int k0 = k;
	int last = n-1;
	if(k0%2){
		if(a[n-1]<=0){
			mint ans = 1;
			for(int i=0; i<k0; i++){
				ans *= a[n-1-i];
			}
			return ans.x;
		}
		ans *= a[n-1];
		last--;
		k0--;
	}

	int start = 0;
	for(int i=0; i<k0/2; i++){
		ll p = a[last] * a[last-1];
		ll q = a[start] * a[start+1];
		if(p<q){
			ans *= q;
			start+=2;
		} else{
			ans *= p;
			last-=2;
		}
	}

	return ans.x;
}

/*
// incorrect:
// e.g.
// n=2, k=2, a={-1, 1}
*/
ll solve0(){
	vector<ll> pa, na, za;
	for(int i=0; i<n; i++){
		if(a[i]>=0) pa.push_back(a[i]);
		else if(a[i]<0) na.push_back(a[i]);
	}
	sort(pa.rbegin(), pa.rend());
	sort(na.rbegin(), na.rend());

	if(na.size()==n&&k%2>0){
		mint ans = 1;
		for(int i=0; i<k; i++){
			ans *= na[i];
		}
		return ans.x;
	//} else if((k%2==0||pa.size()>0)&&na.size()/2*2+pa.size()>=k){
	} else {
		dbg(pa);
		dbg(na);
		mint ans = 1;
		if(k%2){
			ans *= pa[0];
		}

		vector<ll> xs;
		for(int i=0; i<na.size()/2; i++){
			xs.push_back(na[na.size()-1-2*i] * na[na.size()-1-2*i-1]);
		}
		for(int i=0; i<(pa.size()-k%2)/2; i++){
			xs.push_back(pa[k%2+2*i] * pa[k%2+2*i+1]);
		}
		sort(xs.rbegin(), xs.rend());
		for(int i=0; i<k/2; i++) ans *= xs[i];

		return ans.x;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;

	cin >> n >> k;
	a = vector<ll>(n);
	cin >> a;

	cout << solve() << endl;

	return 0;
}

