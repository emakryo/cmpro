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

template <class T>
struct Bit{
	std::vector<T> v;
	Bit(int n) {
		v.assign(n, 0);
	}
	// i must be 0 <= i < n
	T sum(int i){
		T s=0;
		while(i>0){
			s += v[i];
			i -= i & -i;
		}
		return s;
	}
	// i must be 1 <= i < n
	void add(int i, T x){
		while(i < v.size()){
			v[i] += x;
			i += i & -i;
		}
	}
};

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

const ll Mod = 998244353;
int main(){
	int N;
	cin >> N;
	vector<pair<int, int>> P(N);
	for(int i=0; i<N; i++) cin >> P[i].first >> P[i].second;

	for(int i=0; i<N; i++) swap(P[i].first, P[i].second);
	sort(P.begin(), P.end());
	for(int i=0; i<N; i++) P[i].first = i;
	for(int i=0; i<N; i++) swap(P[i].first, P[i].second);
	sort(P.begin(), P.end());
	for(int i=0; i<N; i++) P[i].first = i;

	Bit<int> inc(N+1);
	vector<int> leftlow(N), lefthigh(N);
	for(int i=0; i<N; i++){
		leftlow[i] = inc.sum(P[i].second+1);
		lefthigh[i] = i-leftlow[i];
		inc.add(P[i].second+1, 1);
	}

	Bit<int> dec(N+1);
	vector<int> rightlow(N), righthigh(N);
	for(int i=N-1; i>=0; i--){
		rightlow[i] = dec.sum(P[i].second+1);
		righthigh[i] = N-i-1-rightlow[i];
		dec.add(P[i].second+1, 1);
	}
	debug(leftlow);
	debug(lefthigh);
	debug(rightlow);
	debug(righthigh);

	mint ans(0, Mod);
	vector<mint> pow2(N+5, mint(0, Mod));
	pow2[0] = 1;
	for(int i=1; i<N+5; i++) pow2[i] = pow2[i-1] * 2;
	for(int i=0; i<N; i++){
		mint x = pow2[N] - 1
			- pow2[rightlow[i]+righthigh[i]]
			- pow2[leftlow[i]+lefthigh[i]]
			- pow2[rightlow[i]+leftlow[i]]
			- pow2[righthigh[i]+lefthigh[i]]
			+ pow2[rightlow[i]]
			+ pow2[righthigh[i]]
			+ pow2[leftlow[i]]
			+ pow2[lefthigh[i]];
		ans += x;
		debug(any{x.x});
	}
	cout << ans.x << endl;

	return 0;
}
