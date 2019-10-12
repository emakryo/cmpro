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

ll m = 1e9+7;
struct mint {
	typedef long long ll;
	ll x;
	mint(ll x=0): x(x%m) {}
	mint operator-() const { return mint(m-x); }
	mint operator+(const mint o) const { return mint(x+o.x); }
	mint operator-(const mint o) const { return mint(x-o.x+m); }
	mint operator*(const mint o) const { return mint(x*o.x); }
	mint& operator+=(const mint o) { x = (x+o.x)%m; return *this; }
	mint& operator-=(const mint o) { x = (x-o.x+m)%m; return *this; }
	mint& operator*=(const mint o) { x = x*o.x%m; return *this; }
	bool operator==(const mint o) const { return x==o.x; }
	bool operator!=(const mint o) const { return x!=o.x; }
	template<typename T> mint& operator=(const T o) { x = o%m; return *this; }
	template<typename T> mint operator+(const T o) const { return mint(x+o); }
	template<typename T> mint operator-(const T o) const { return mint(x-((ll)o)%m+m); }
	template<typename T> mint operator*(const T o) const { return mint(x*o); }
	template<typename T> mint& operator+=(const T o) { x = (x+(ll)o%m)%m; return *this; }
	template<typename T> mint& operator-=(const T o) { x = (x-((ll)o)%m+m)%m; return *this; }
	template<typename T> mint& operator*=(const T o) { x = x*((ll)o%m)%m; return *this; }
	template<typename T> bool operator==(const T o) const { return x==o%m; }
	template<typename T> bool operator!=(const T o) const { return x!=o%m; }

	mint pow(ll k) const {
		if(k==0) return mint(1);
		if(k%2) return pow(k-1)*x;
		mint z = pow(k/2);
		return z*z;
	}

	mint inv() const { return pow(m-2); }
};

mint dp[5001][5001];

int main(){
	int N;
	cin >> N;
	string S;
	cin >> S;
	int K = S.size();

	dp[0][0] = 1;
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if(j>0){
				dp[i+1][j-1] += dp[i][j];
			} else {
				dp[i+1][j] += dp[i][j];
			}
			dp[i+1][j+1] += dp[i][j]*2;
		}
	}
	debug(dp[N][K], mint(2).pow(K).inv());
	cout << (dp[N][K] * mint(2).pow(K).inv()).x << endl;

	return 0;
}
