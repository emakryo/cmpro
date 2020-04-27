#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> anys;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(anys{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

int main(){
	string S;
	cin >> S;
	vector<int> cnt1(2019), cnt2(2019);
	ll ans = 0;

	for(int i=0; i<S.size(); i++){
		for(int j=0; j<2019; j++){
			cnt2[(10*j+S[i]-'0')%2019] = cnt1[j];
		}
		cnt2[S[i]-'0']++;
		ans += cnt2[0];
		cnt1=cnt2;
	}
	cout << ans << endl;

	return 0;
}
