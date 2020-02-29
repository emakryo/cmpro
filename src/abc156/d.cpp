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

int _main(){
	for(auto x: std::vector<int>{3, 5, 7, 11, 13, 17, 19}){
		assert((mint(4, x)*mint(4, x).inv())==1);
	}
	return 0;
}

int main(){
	ll N, A, B;
	cin >> N >> A >> B;

	mint ans = mint(2).pow(N) - 1;
	mint xa = mint(1);
	for(int i=0; i<A; i++){
		xa *= mint(N-i) * mint(i+1).inv();
	}
	ans -= xa;
	mint xb = mint(1);
	for(int i=0; i<B; i++){
		xb *= mint(N-i) * mint(i+1).inv();
	}
	ans -= xb;
	cout << ans.x << endl;

	return 0;
}
