#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

const ll P = 1e9+7;
int main(){
	ll N;
	int K;
	cin >> N >> K;

	map<ll, ll> divm;
	for(ll i=1; i*i<=N; i++){
		divm[i] = N/i;
		if(i*i!=N) divm[N/i] = i;
	}
	vector<ll> div;
	for(auto p: divm) div.push_back(p.first);

	int ndiv = div.size();
	vector<ll> dp(ndiv);
	dp[0] = 1;
	for(int i=0; i<=K; i++){
		vector<ll> next(ndiv);
		ll s = dp[0];
		next[ndiv-1] = s;
		for(int j=1; j<ndiv; j++){
			s += dp[j]*(div[j]-div[j-1])%P;
			s %= P;
			next[ndiv-1-j] = s;
		}
		dp = next;
	}

	cout << dp[0] << endl;

	return 0;
}
