#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
struct mint;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*, mint>> any;
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
	friend ostream& operator<<(ostream &os, const mint x) { return os << x.x; }

	mint pow(ll k) const {
		if(k==0) return mint(1, m);
		if(k%2) return pow(k-1)*x;
		mint z = pow(k/2); return z*z;
	}

	mint inv() const { return pow(m-2); }
};

mint fact[500000];
mint fact_inv[500000];

void init_fact(){
	fact[0] = mint(1);
	for(int i=1; i<500000; i++) fact[i] = fact[i-1]*i;
	fact_inv[0] = mint(1);
	for(int i=1; i<500000; i++) fact_inv[i] = fact_inv[i-1]/i;
}

struct Elem {
	int n;
	mint x;
	Elem():n(0), x(1){}
	Elem& operator+=(Elem &c) {
		x *= c.x * fact_inv[c.n];
		n += c.n;
		return *this;
	}
	Elem add_self() const {
		Elem ret(*this);
		ret.x *= fact[ret.n];
		ret.n++;
		return ret;
	}
	Elem operator-(Elem &o) const {
		Elem ret(*this);
		ret.n -= o.n;
		ret.x *= fact[o.n] / o.x;
		return ret;
	}
};

Elem dp[200005];
vector<vector<int>> graph;

void dfs(int u, int p){
	for(int v: graph[u]) {
		if(v==p) continue;
		dfs(v, u);
		dp[u] += dp[v];
	}
	dp[u] = dp[u].add_self();
}

void omnidirect(int u, int p){
	Elem sum;
	for(int v: graph[u]){
		sum += dp[v];
	}
	for(int v: graph[u]){
		if(v==p) continue;
		dp[u] = (sum - dp[v]).add_self();
		omnidirect(v, u);
	}
	dp[u] = sum.add_self();
}

int main(){
	int N;
	cin >> N;
	vector<int> A(N-1), B(N-1);
	for(int i=0; i<N-1; i++) cin >> A[i] >> B[i];
	graph.assign(N, vector<int>());
	for(int i=0; i<N-1; i++){
		A[i]--; B[i]--;
		graph[A[i]].push_back(B[i]);
		graph[B[i]].push_back(A[i]);
	}

	init_fact();

	dfs(0, -1);
	omnidirect(0, -1);

	for(int i=0; i<N; i++){
		cout << dp[i].x << endl;
	}
	return 0;
}
