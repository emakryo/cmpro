#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
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
	mint(ll x=0, ll m=1e9+7): x(x%m), m(m) {}
	mint operator-() const { return mint(m-x, m); }
	mint operator+(const mint o) const { return mint(x+o.x, m); }
	mint operator-(const mint o) const { return mint(x-o.x+m, m); }
	mint operator*(const mint o) const { return mint(x*o.x, m); }
	mint& operator+=(const mint o) { x = (x+o.x)%m; return *this; }
	mint& operator-=(const mint o) { x = (x-o.x+m)%m; return *this; }
	mint& operator*=(const mint o) { x = x*o.x%m; return *this; }
	bool operator==(const mint o) const { return x==o.x; }
	bool operator!=(const mint o) const { return x!=o.x; }
	template<typename T> mint& operator=(const T o) { x = o%m; return *this; }
	template<typename T> mint operator+(const T o) const { return mint(x+o, m); }
	template<typename T> mint operator-(const T o) const { return mint(x-((ll)o)%m+m, m); }
	template<typename T> mint operator*(const T o) const { return mint(x*o, m); }
	template<typename T> mint& operator+=(const T o) { x = (x+(ll)o%m)%m; return *this; }
	template<typename T> mint& operator-=(const T o) { x = (x-((ll)o)%m+m)%m; return *this; }
	template<typename T> mint& operator*=(const T o) { x = x*((ll)o%m)%m; return *this; }
	template<typename T> bool operator==(const T o) const { return x==o%m; }
	template<typename T> bool operator!=(const T o) const { return x!=o%m; }

	mint pow(ll k) const {
		if(k==0) return mint(1, m);
		if(k%2) return pow(k-1)*x;
		mint z = pow(k/2);
		return z*z;
	}

	mint inv() const { return pow(m-2); }
};

mint dp[2][305][305];
int main(){
	int N, K;
	cin >> N >> K;
	string S;
	cin >> S;

	dp[0][0][0] = 1;
	for(int i=0; i<N; i++){
		for(int p=0; p<=K; p++) for(int q=0; q<=K; q++) dp[(i+1)%2][p][q] = 0;
		int n_pos = 0;
		for(int p=0; p<=K; p++) for(int q=0; q<=K; q++) {
			debug(i, p, q, dp[i%2][p][q].x);
			if(dp[i%2][p][q] != 0) n_pos++;
			if(S[i]=='?' || S[i]=='0'){
				if(q>0) dp[(i+1)%2][p+1][q-1] += dp[i%2][p][q];
				else dp[(i+1)%2][p+1][q] += dp[i%2][p][q];
			}
			if(S[i]=='?' || S[i]=='1'){
				if(p>0) dp[(i+1)%2][p-1][q+1] += dp[i%2][p][q];
				else dp[(i+1)%2][p][q+1] += dp[i%2][p][q];
			}
		}
		debug(n_pos);
	}

	mint ans;
	for(int p=0; p<=K; p++) for(int q=0; q<=K; q++) ans += dp[N%2][p][q];

	cout << ans.x << endl;

	return 0;
}
