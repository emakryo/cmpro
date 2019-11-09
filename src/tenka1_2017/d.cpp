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
	ll K;
	cin >> N >> K;
	vector<ll> A(N), B(N);
	for(int i=0; i<N; i++){
		cin >> A[i] >> B[i];
	}

	ll ans = 0;
	for(int k=30; k>=0; k--){
		if(((K>>k)&1)==0) continue;
		ll sum = 0;
		ll o = 0;
		for(int i=0; i<N; i++){
			ll a = A[i] >> k;
			ll x = (K >> (k+1)) << 1;
			if(a + (x & ~a) == x){
				sum += B[i];
				o |= A[i];
			}
		}
		ans = max(ans, sum);
		debug(k, sum, o);
	}

	ll sum = 0;
	for(int i=0; i<N; i++){
		if(A[i]+(K&~A[i])==K){
			sum += B[i];
		}
	}
	ans = max(sum, ans);

	cout << ans << endl;

	return 0;
}
