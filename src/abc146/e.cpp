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
	vector<ll> A(N);
	for(int i=0; i<N; i++) cin >> A[i];

	vector<ll> sum(N+1);
	for(int i=0; i<N; i++) sum[i+1] = (sum[i]+A[i])%K;
	vector<ll> x(N+1);
	for(int i=0; i<=N; i++) x[i] = (sum[i]-i%K+K)%K;
	debugv(x);

	map<ll, int> cnt;
	for(int i=0; i<min(K, (ll)N+1); i++) cnt[x[i]]++;

	ll ans = 0;
	for(int i=0; i<N; i++){
		cnt[x[i]]--;
		debug(i, cnt[x[i]]);
		ans += cnt[x[i]];
		if(i+K<=N) cnt[x[i+K]]++;
	}
	cout << ans << endl;

	return 0;
}
