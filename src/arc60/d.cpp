#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

// list all divisors of n. O(sqrt(n))
std::vector<ll> get_divisors(ll n){
	std::vector<ll> div(1, 1);
	for(int i=2; (ll)i*i<=n; i++){
		if(n%i==0) div.push_back(i);
	}
	for(int i=div.size()-1; i>=0; i--){
		if(div[i]*div[i]==n) continue;
		div.push_back(n/div[i]);
	}
	return div;
}

int main(){
	ll N, S;
	cin >> N >> S;
	if(N==S){
		cout << N+1 << endl;
		return 0;
	}
	if(N<S){
		cout << -1 << endl;
		return 0;
	}

	vector<ll> divs = get_divisors(N-S);
	sort(divs.begin(), divs.end());
	ll ans = 1e18;
	for(ll x: divs){
		ll b = x+1;
		ll n = N;
		ll s = 0;
		while(n>0){
			s += n%b;
			n /= b;
		}
		if(s == S){
			ans = min(ans, b);
		}
	}
	if(ans < 1e18) cout << ans << endl;
	else cout << -1 << endl;

	return 0;
}
