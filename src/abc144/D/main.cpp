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

int main() {
	long long a;
    scanf("%lld",&a);
    long long b;
    scanf("%lld",&b);
    long long x;
    scanf("%lld",&x);

	cout << setprecision(20);
	if (x <= a*a*b/2){
		double y = 2.0*x/(a*b);
		cout << atan(b/y) * 180 / M_PI;
	} else {
		double y = 2.0*x/(a*a) - b;
		cout << atan((b-y)/a) * 180 / M_PI;
	}
	return 0;
}
