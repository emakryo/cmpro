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

int N;
ll K;
ll A[300000], B[300000];

ll count(ll x){
	ll ret = 0;
	for(int i=0; i<N; i++){
		ret += upper_bound(B, B+N, x/A[i]) - B;
	}
	return ret;
}

int main(){
	cin >> N >> K;
	for(int i=0; i<N; i++) cin >> A[i];
	for(int i=0; i<N; i++) cin >> B[i];

	sort(A, A+N);
	sort(B, B+N);

	ll lb=0, ub=1LL<<62;
	while(ub-lb>1){
		ll x = (lb+ub)/2;
		if(count(x) < K){
			lb = x;
		} else {
			ub = x;
		}
	}
	cout << ub << endl;

	return 0;
}
