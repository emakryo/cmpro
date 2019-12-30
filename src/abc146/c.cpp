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

int main(){
	ll A, B, X;
	cin >> A >> B >> X;

	ll ans = 0;
	ll e10 = 1;
	for(int d=1; d<=10; d++){
		e10 *= 10;
		ll n = (X-B*d)/A;
		if(n>=e10) n = e10-1;
		ans = max(ans, n);
	}
	cout << min((ll)1e9, ans) << endl;

	return 0;
}
