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
	vector<int> B(N);
	for(int i=0; i<N-1; i++) cin >> B[i];

	ll ans = B[0]+B[N-2];
	for(int i=1; i<N-1; i++){
		ans += min(B[i], B[i-1]);
	}
	cout << ans << endl;


	return 0;
}
