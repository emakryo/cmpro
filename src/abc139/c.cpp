#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double>> any;
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
	vector<ll> H(N);
	for(int i=0; i<N; i++) cin >> H[i];

	ll ans = 0;
	ll cnt = 0;
	for(int i=0; i<N-1; i++){
		if(H[i]>=H[i+1]) cnt++;
		else cnt = 0;
		ans = max(ans, cnt);
	}

	cout << ans << endl;



	return 0;
}
