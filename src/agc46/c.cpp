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
	mint(ll x=0, ll m=998244353): x((m+x%m)%m), m(m) {}
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

const int Nmax = 305;
mint dp[Nmax][Nmax][Nmax];

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;

	string S; cin >> S;
	ll K; cin >> K;

	vector<int> x(1, 0);
	int m = 0;
	for(int i=0; i<S.size(); i++){
		if(S[i]=='0'){
			x.push_back(0);
		} else {
			x.back()++;
			m++;
		}
	}

	dbg(x);

	int n = x.size();
	K = min(K, (ll)Nmax-1);

	dp[0][0][0] = 1;
	for(int i=0; i<n; i++){
		for(int k=0; k<=K; k++){
			for(int l=k; l>=0; l--){
				dp[i+1][l][k] = dp[i+1][l+1][k] + dp[i][l][k];
			}
		}
		for(int k=0; k<=K; k++){
			for(int l=k; l>=0; l--){
				for(int j=1; j<=x[n-i-1]; j++){
					if(l-j>=0&&k-j>=0) dp[i+1][l][k] += dp[i][l-j][k-j];
				}
				dbg(i, k, l, dp[i+1][l][k]);
			}
		}
	}

	mint ans = 0;
	for(int k=0; k<=K; k++){
		ans += dp[n][0][k];
	}

	cout << ans << endl;

	return 0;
}
