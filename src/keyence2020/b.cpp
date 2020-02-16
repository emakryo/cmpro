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
	int N; cin >> N;
	vector<ll> X(N), L(N);
	for(int i=0; i<N; i++) cin >> X[i] >> L[i];

	vector<pair<ll, int>> right(N);
	for(int i=0; i<N; i++) right[i] = {X[i]+L[i], i};
	sort(right.begin(), right.end());

	int ans = 0;
	ll x = -1e10;
	for(int i=0; i<N; i++){
		int r = right[i].first;
		int n = right[i].second;
		if(r-2*L[n]<x) continue;
		x = r;
		ans++;
	}

	cout << ans << endl;

	return 0;
}
