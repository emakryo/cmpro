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

	int ans = 0;

	set<ll> cand;
	for(ll k=1; k*k<=N; k++){
		if(N%k==0){
			cand.insert(N/k);
			cand.insert(k);
		}
		if((N-1)%k==0){
			cand.insert((N-1)/k);
			cand.insert(k);
		}
	}

	for(ll k: cand){
		if(k==1) continue;
		ll n = N;
		while(n%k==0) n/=k;
		if((n-1)%k==0) ans++;
	}

	cout << ans << endl;

	return 0;
}
