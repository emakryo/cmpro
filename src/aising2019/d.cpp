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

int N, Q;
vector<ll> A;
vector<ll> cumsum, esum;
void solve(){
	int x;
	cin >> x;

	int lb = 0, ub = (N+1)/2;
	while(ub-lb>1){
		int k = (ub+lb)/2;
		int l = max(0, N-1-2*k);
		//debug(x, k, lb, ub, l, abs(x-A[N-1-k]), abs(x-A[l]));
		if(abs(x-A[N-1-k])<abs(x-A[l])){
			ub = k;
		} else {
			lb = k;
		}
		//debug(lb, ub);
	}
	debug(x, ub);

	ll ans = cumsum[N-1]-cumsum[N-1-ub];
	if(N%2){
		if(N-1-2*ub>=0) ans += esum[N-1-2*ub];
	} else {
		if(N-1-2*ub>=1) ans += cumsum[N-1-2*ub]-esum[N-2-2*ub];
	}
	cout << ans << endl;
}


int main(){
	cin >> N >> Q;
	A.assign(N, 0);
	for(int i=0; i<N; i++) cin >> A[i];

	cumsum.assign(N, 0);
	esum.assign(N, 0);
	cumsum[0] = A[0];
	esum[0] = A[0];
	for(int i=1; i<N; i++){
		cumsum[i] = cumsum[i-1]+A[i];
		esum[i] = esum[i-1] + (i%2?0:A[i]);
	}
	for(int q=0; q<Q; q++) solve();

	return 0;
}
