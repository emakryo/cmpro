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
	int T[2];
	ll A[2], B[2];
	cin >> T[0] >> T[1];
	cin >> A[0] >> A[1];
	cin >> B[0] >> B[1];

	ll xa, xb;
	xa = A[0]*T[0]+A[1]*T[1];
	xb = B[0]*T[0]+B[1]*T[1];
	if(xa == xb){
		cout << "infinity" << endl;
		return 0;
	}

	if(xa > xb){
		swap(A[0], B[0]);
		swap(A[1], B[1]);
		swap(xa, xb);
	}

	ll x = xb - xa;
	ll y = A[0]*T[0] - B[0]*T[0];
	if(y < 0) {
		cout << 0 << endl;
		return 0;
	}

	debug(x, y, y % x);

	ll ans = 0;
	if(y % x == 0){
		ans = 2 * (y / x - 1) + 2;
	} else {
		ans = 2 * (y / x) + 1;
	}
	cout << ans << endl;

	return 0;
}
