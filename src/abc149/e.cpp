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
	ll N, M;
	cin >> N >> M;
	vector<ll> A(N);
	for(int i=0; i<N; i++) cin >> A[i];
	sort(A.begin(), A.end());
	reverse(A.begin(), A.end());

	vector<ll> cum(N);
	cum[0] = A[0];
	for(int i=1; i<N; i++) cum[i] = cum[i-1] + A[i];

	ll ub = 1e12, lb = 0;
	map<ll, pair<ll, ll>> m;
	while(ub-lb>1){
		ll z = (lb+ub)/2;

		ll count = 0;
		ll total = 0;
		for(int i=0; i<N; i++){
			int ubi = N, lbi = 0;
			if(A[0]+A[i]<z) continue;

			while(ubi-lbi>1){
				int k = (ubi+lbi)/2;
				if(A[k]+A[i]>=z){
					lbi = k;
				} else {
					ubi = k;
				}
			}
			int k = lbi;
			total += cum[k] + A[i]*(k+1);
			count += (k+1);
			debug(" ", z, i, k);
		}

		m[z] = {count, total};
		debug(z, count, total);
		if(count > M) lb = z;
		else ub = z;
	}

	debug(lb, ub);
	ll ans = m[ub].second + lb * (M - m[ub].first);
	cout << ans << endl;

	return 0;
}
