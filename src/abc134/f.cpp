#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

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
	template<typename T> mint operator+(const T o) const { return mint(x+o, m); }
	template<typename T> mint operator-(const T o) const { return mint(x-((ll)o)%m+m, m); }
	template<typename T> mint operator*(const T o) const { return mint(x*o, m); }
	template<typename T> mint& operator+=(const T o) { x = (x+(ll)o%m)%m; return *this; }
	template<typename T> mint& operator-=(const T o) { x = (x-((ll)o)%m+m)%m; return *this; }
	template<typename T> mint& operator*=(const T o) { x = x*((ll)o%m)%m; return *this; }
	template<typename T> mint& operator=(const T o) { x = o%m; return *this; }
};

mint dp[55][55][1300];
int main(){
	int N, K;
	cin >> N >> K;

	dp[0][0][0] = 1;
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			for(int k=0; k<=N*N/2; k++){
				debug(any{i, j, k, dp[i][j][k].x});
				dp[i+1][j][k+j] += dp[i][j][k];
				dp[i+1][j+1][k+j] += dp[i][j][k];
				dp[i+1][j][k+j] += dp[i][j][k]*2*j;
				if(j>0) dp[i+1][j-1][k+j] += dp[i][j][k]*j*j;
			}
		}
	}

	ll ans;
	if(K%2) ans = 0;
	else ans = dp[N][0][K/2].x;
	cout << ans << endl;

	return 0;
}
