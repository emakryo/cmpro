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
};

mint dp[63][2][2][2];
int main(){
	ll L, R;
	cin >> L >> R;

	dp[62][0][0][0] = 1;
	for(int k=61; k>=0; k--){
		int l = (L>>k)&1;
		int r = (R>>k)&1;
		for(int p=0; p<2; p++) for(int q=0; q<2; q++) for(int s=0; s<2; s++){
			mint a = dp[k+1][p][q][s];
			debug(any{k+1, l, r, p, q, s, a.x});
			for(int x=0; x<2; x++) for(int y=0; y<2; y++){
				if(x && !y) continue;
				if(!s && x!=y) continue;
				int np = p;
				int nq = q;
				int ns = s;
				if(x && y) ns = 1;
				if(!p && l < x) np = 1;
				if(!p && x < l) continue;
				if(!q && y < r) nq = 1;
				if(!q && r < y) continue;
				dp[k][np][nq][ns] += a;
			}
		}
	}

	mint ans(0);
	for(int p=0; p<2; p++) for(int q=0; q<2; q++) for(int r=0; r<2; r++){
		ans += dp[0][p][q][r];
	}

	cout << ans.x << endl;

	return 0;
}
