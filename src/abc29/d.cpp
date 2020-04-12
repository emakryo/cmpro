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
	ll N;
	cin >> N;

	ll d = 1;
	ll ans = 0;
	for(int k=0; k<10; k++){
		int high = N/d;
		int low = N%d;
		int n_digit = 0;
		if(high%10==0){
			n_digit += high/10 * d;
		} else if(high%10==1){
			n_digit += high/10 * d + (low+1);
		} else {
			n_digit += (high/10 + 1) * d;
		}

		debug(k, n_digit);
		ans += n_digit;
		d *= 10;
	}

	cout << ans << endl;

	return 0;
}
