#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> anys;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(anys{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

ll gcd(ll x, ll y){
	if(y==0) return x;
	return gcd(y, x%y);
}

int main(){
	int N;
	ll X, D;
	cin >> N >> X >> D;

	if(D==0){
		if(X==0){
			cout << 1 << endl;
		} else {
			cout << N+1 << endl;
		}
		return 0;
	}

	ll g = gcd(abs(X), abs(D));
	X /= D / abs(D) * g;
	D /= D / abs(D) * g;

	debug(X, D);
	vector<ll> L(N+1), R(N+1);
	for(ll m=0; m<=N; m++){
		ll k = (m - m%D)/D;
		L[m] = m*(m-1)/2 + k*X;
		R[m] = m*(2*N-m-1)/2 + k*X+1;
		debug(m, L[m], R[m]);
	}

	ll ans = 0;
	for(int k=0; k<=min((ll)N, D-1); k++){
		vector<pair<ll, int>> vs;
		for(int i=k; i<=N; i+=D) {
			vs.push_back({L[i], i});
			vs.push_back({R[i], i+N+1});
		}
		sort(vs.begin(), vs.end());
		ll start = 1e18;
		int l = 0;
		for(auto p: vs){
			if(p.second<N+1){
				start = min(start, p.first);
				l++;
			} else {
				l--;
				if(l==0) {
					ans += p.first-start;
					start = 1e18;
				}
			}
			debug(p.first, p.second, l, start);
		}
	}

	cout << ans << endl;

	return 0;
}
