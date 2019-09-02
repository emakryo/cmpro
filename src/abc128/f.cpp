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

int main(){
	int N;
	cin >> N;
	vector<ll> S(N);
	for(int i=0; i<N; i++) cin >> S[i];

	ll ans = 0;
	for(int d=1; d<=(N-1)/2; d++){
		ll sum = 0;
		set<int> used;
		for(int k=1; d*(k+1)<N-1; k++){
			if(d*k==N-1-d*k||used.count(d*k)>0||used.count(N-1-d*k)>0) break;
			sum += S[d*k] + S[N-1-d*k];
			used.insert(d*k);
			used.insert(N-1-d*k);
			ans = max(ans, sum);
			debug(any{d, k, d*k, N-1-d*k, sum});
		}
	}

	cout << ans << endl;

	return 0;
}
