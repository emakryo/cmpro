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

using DP = vector<vector<vector<mint>>>;
using Gr = vector<vector<int>>;

void dfs(int v, int p, Gr &graph, DP &dp){
	int k = dp[v].size();
	vector<vector<mint>> vdp(k, vector<mint>(3));
	vdp[0][0] = 1;
	for(int u: graph[v]){
		if(u==p) continue;
		dfs(u, v, graph, dp);

		vector<vector<mint>> next(k, vector<mint>(3));
		for(int i=0; i<k; i++){
			for(int l=0; l<k; l++){
				for(int j=0; j<3; j++){
					if(i+l<k){
						next[i+l][j] += vdp[i][j] * (dp[u][l][0]+dp[u][l][1]+dp[u][l][2]);
					}
				}
				if(i+l+1<k) next[i+l+1][1] += vdp[i][0] * dp[u][l][0];
				if(i+l<k) next[i+l][1] += vdp[i][0] * dp[u][l][1];
				if(i+l<k) next[i+l][2] += vdp[i][1] * dp[u][l][0];
				if(0<=i+l-1&&i+l-1<k) next[i+l-1][2] += vdp[i][1] * dp[u][l][1];
			}
		}
		vdp = next;
	}
	dp[v] = vdp;

	dbg(v);
	for(int i=0; i<k; i++){
		dbg(dp[v][i]);
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;

	int n, k; cin >> n >> k;
	Gr graph(n);
	for(int i=0; i<n-1; i++){
		int a,b; cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	DP dp(n, vector<vector<mint>>(k+1, vector<mint>(3)));

	dfs(0, -1, graph, dp);

	cout << dp[0][k][0] + dp[0][k][1] + dp[0][k][2] << endl;

	return 0;
}
