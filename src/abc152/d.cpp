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
	int N;
	cin >> N;

	ll ans = 0;
	for(int i=1; i<=N; i++){
		int ha = i;
		while(ha>=10) ha /= 10;
		int ta = i%10;
		if(ta == 0) continue;

		if(ha == ta) ans+=1;
		int ta1 = ta+1;
		ta *= 10;
		ta1 *= 10;
		for(int k=0; k<5; k++){
			int upper = ta1 + ha - 10;
			int lower = ta + ha;
			debug(lower, upper);
			if(lower > N) break;
			if(upper > N) {
				ans += (N - lower + 10) / 10;
				break;
			} else {
				ans += (upper - lower + 10) / 10;
				ta *= 10;
				ta1 *= 10;
			}
		}
	}

	cout << ans << endl;

	return 0;
}
