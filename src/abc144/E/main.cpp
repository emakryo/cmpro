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
	long long N;
    scanf("%lld",&N);
    long long K;
    scanf("%lld",&K);
    std::vector<long long> A(N);
    for(int i = 0 ; i < N ; i++){
        scanf("%lld",&A[i]);
    }
    std::vector<long long> F(N);
    for(int i = 0 ; i < N ; i++){
        scanf("%lld",&F[i]);
    }

	sort(A.begin(), A.end());
	sort(F.begin(), F.end());

	ll sum = 0;
	for(int i=0; i<N; i++) sum += A[i];
	if(sum <= K){
		cout << 0 << endl;
		return 0;
	}

	ll lb=0, ub=1e13;
	while(ub-lb>1){
		ll x = (lb+ub)/2;

		ll l = 0;
		for(int i=0; i<N; i++){
			l += max(0ll, A[i]-x/F[N-i-1]);
		}
		if(l <= K){
			ub = x;
		} else {
			lb = x;
		}
	}

	cout << ub << endl;

	return 0;
}
