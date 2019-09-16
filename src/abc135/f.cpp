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

// Z array: Z[i] = maximum n s.t. str[0..n] == str[i..i+n]
std::vector<int> getZarray(std::string str) {
	int n = str.length();
	vector<int> Z(n);
	int L, R, k;
	// [L,R] make a window which matches with prefix of s
	L = R = 0;
	for (int i=1; i<n; i++) {
		// if i>R nothing matches so we will calculate.
		// Z[i] using naive way.
		if (i > R) {
			L = R = i;
			// R-L = 0 in starting, so it will start
			// checking from 0'th index. For example,
			// for "ababab" and i = 1, the value of R
			// remains 0 and Z[i] becomes 0. For string
			// "aaaaaa" and i = 1, Z[i] and R become 5
			while (R<n && str[R-L] == str[R]) R++;
			Z[i] = R-L;
			R--;
		} else {
			// k = i-L so k corresponds to number which
			// matches in [L,R] interval.
			k = i-L;
			// if Z[k] is less than remaining interval
			// then Z[i] will be equal to Z[k].
			// For example, str = "ababab", i = 3, R = 5
			// and L = 2
			if (Z[k] < R-i+1) Z[i] = Z[k];
			// For example str = "aaaaaa" and i = 2, R is 5,
			// L is 0
			else {
				// else start from R and check manually
				L = i;
				while (R<n && str[R-L] == str[R]) R++;
				Z[i] = R-L;
				R--;
			}
		}
	}
	return Z;
}

int main(){
	string S, T;
	cin >> S;
	cin >> T;
	int ns = S.size();
	int nt = T.size();

	string sn;
	while(sn.size() < ns+nt) sn += S;

	vector<int> zarr = getZarray(T+"$"+sn);
	for(int i=0; i<sn.size(); i++) zarr[i] = zarr[i+nt+1];
	zarr.resize(sn.size());

	vector<bool> match(ns, false);
	for(int i=0; i<ns; i++){
		match[i] = zarr[i] >= nt;
	}
	debug(match);

	int ans = 0;
	vector<int> height(ns, -1);
	for(int i=0; i<ns; i++){
		if(!match[i]) continue;
		if(height[i]>0) continue;
		int h = 1;
		mint j(i+nt, ns);
		while(j!=i && match[j.x]){
			if(height[j.x] > 0){
				h += height[j.x];
				break;
			} else {
				j += nt;
				h++;
			}
		}
		if(j==i){
			cout << -1 << endl;
			return 0;
		}
		ans = max(ans, h);
		j = i;
		while(match[j.x] && height[j.x]<0){
			height[j.x] = h--;
			j += nt;
		}
	}
	debug(height);

	cout << ans << endl;

	return 0;
}
