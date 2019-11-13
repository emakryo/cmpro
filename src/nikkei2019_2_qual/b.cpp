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

const ll P = 998244353;
int main(){
	int N;
	cin >> N;
	vector<int> D(N);
	for(int i=0; i<N; i++) cin >> D[i];

	vector<int> cnt(N);
	int mx = 0;
	for(int i=0; i<N; i++){
		cnt[D[i]]++;
		mx = max(mx, D[i]);
	}

	if(D[0]!=0){
		cout << 0 << endl;
		return 0;
	}
	if(cnt[0]!=1){
		cout << 0 << endl;
		return 0;
	}
	bool ok = true;
	for(int i=0; i<=mx; i++){
		if(cnt[i]==0){
			cout << 0 << endl;
			return 0;
		}
	}

	ll ans = 1;
	for(int i=1; i<N; i++){
		for(int k=0; k<cnt[i]; k++){
			ans *= cnt[i-1];
			ans %= P;
		}
	}
	cout << ans << endl;

	return 0;
}
