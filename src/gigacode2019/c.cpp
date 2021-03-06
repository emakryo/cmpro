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

const ll INF = 1e18;

int main(){
	int D;
	cin >> D;
	vector<ll> A(D), B(D);
	for(int i=0; i<D; i++) cin >> A[i];
	for(int i=0; i<D; i++) cin >> B[i];

	ll ans = INF;
	ll cum = 0;
	for(int i=0; i<D; i++){
		cum += A[i];
		if(cum >= B[i]){
			ans = min(ans, B[i]);
		}
	}
	if(ans == INF){
		cout << -1 << endl;
	} else {
		cout << ans << endl;
	}


	return 0;
}
