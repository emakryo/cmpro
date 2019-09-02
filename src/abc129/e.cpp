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
	string L;
	const ll P = 1e9+7;
	cin >> L;

	vector<ll> e3(L.size());
	e3[0] = 1;
	for(int i=1; i<L.size(); i++) e3[i] = 3*e3[i-1]%P;
	ll ans = 1;
	for(int i=L.size()-1; i>=0; i--){
		if(L[i]=='1'){
			ans = 2*ans + e3[L.size()-1-i];
			ans %= P;
		}
	}

	cout << ans << endl;
	return 0;
}
