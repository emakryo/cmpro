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

int main(){
	int N;
	ll A, B;
	cin >> N >> A >> B;
	vector<ll> S(N);
	for(int i=0; i<N; i++) cin >> S[i];

	ll sum = 0;
	ll smax = S[0], smin = S[0];
	for(ll s: S) {
		sum += s;
		smax = max(smax, s);
		smin = min(smin, s);
	}

	if(smax == smin){
		cout << -1 << endl;
	} else {
		cout << setprecision(20) << (double)B/(smax-smin) << " " << A - (double)B*sum/(N*(smax-smin)) << endl;
	}

	return 0;
}
