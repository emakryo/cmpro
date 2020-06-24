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

vector<vector<mint>> mul(vector<vector<mint>> x, vector<vector<mint>> y){
	vector<vector<mint>> r(x.size(), vector<mint>(y[0].size()));
	for(int i=0; i<x.size(); i++){
		for(int j=0; j<y[0].size(); j++){
			for(int k=0; k<x[0].size(); k++){
				r[i][j] += x[i][k] * y[k][j];
			}
		}
	}
	return r;
}

vector<vector<mint>> pow(vector<vector<mint>> x, ll n){
	if(n==1){
		return x;
	}
	if(n%2){
		return mul(x, pow(x, n-1));
	} else {
		auto z = pow(x, n/2);
		return mul(z, z);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;
	int h, r; cin >> h >> r;
	vector<vector<int>> a(r, vector<int>(r));

	for(int i=0; i<r; i++) cin >> a[i];

	vector<vector<mint>> cnt(r, vector<mint>(r));
	for(int i=0; i<r; i++){
		vector<vector<mint>> dp(1<<r, vector<mint>(r));
		dp[1<<i][i] = 1;
		for(int s=0; s<(1<<r); s++){
			for(int j=0; j<r; j++){
				if((s>>j&1)==0) continue;
				for(int k=0; k<r; k++){
					if(s>>k&1) continue;
					if(a[j][k]==0) continue;
					dp[s|(1<<k)][k] += dp[s][j];
				}
			}
		}

		for(int s=0; s<(1<<r); s++){
			for(int j=0; j<r; j++){
				cnt[i][j] += dp[s][j];
			}
		}
		dbg(cnt[i]);
	}

	vector<vector<mint>> p = pow(cnt, h);
	cout << p[0][0] << endl;
	return 0;
}
